#include <include/vulkan/zwrender.h>
#include <include/vulkan/zwinstance.h>
#include <include/vulkan/zwvalidation.h>
#include <include/vulkan/vulkanconst.h>
#include <include/vulkan/zwphysicaldevice.h>
#include <include/vulkan/zwlogicaldevice.h>
#include <include/vulkan/zwsurface.h>
#include <include/vulkan/zwswapchain.h>
#include <include/vulkan/zwimageview.h>
#include <include/vulkan/zwgraphicpipeline.h>
#include <include/vulkan/zwrenderpass.h>
#include <include/vulkan/zwframebuffers.h>
#include <include/vulkan/zwcommandpool.h>
#include <include/vulkan/zwcommandbuffer.h>
#include <include/vulkan/zwsynchronization.h>
#include <stdexcept>

void ZwRender::init(GLFWwindow* pWindow)
{
	if (!pWindow)
		return;

	m_pZwInstance = new ZwInstance();
	m_pZwInstance->init();

	m_pSurface = new ZwSurface();
	m_pSurface->init(m_pZwInstance, pWindow);

	if (ENABLEVALIDATIONLAYERS)
	{
		m_pValidation = new ZwValidation();
		m_pValidation->init(m_pZwInstance);
	}

	m_pPhysicalDevice = new ZwPhysicalDevice();
	m_pPhysicalDevice->init(m_pZwInstance, m_pSurface);

	m_pLogicalDevice = new ZwLogicalDevice();
	m_pLogicalDevice->init(m_pPhysicalDevice, m_pSurface);

	m_pSwapChain = new ZwSwapChain();
	m_pSwapChain->init(pWindow, m_pPhysicalDevice, m_pSurface, m_pLogicalDevice);

	m_pImageView = new ZwImageView();
	m_pImageView->init(m_pSwapChain, m_pLogicalDevice);

	m_pRenderPass = new ZwRenderPass();
	m_pRenderPass->init(m_pLogicalDevice, m_pSwapChain);

	m_pGraphicPipeline = new ZwGraphicPipeline();
	m_pGraphicPipeline->init(VERTEXSHADERPATH, FRAGMENTSHADERPATH, m_pLogicalDevice, m_pRenderPass);

	m_pFrameBuffers = new ZwFrameBuffers();
	m_pFrameBuffers->init(m_pLogicalDevice, m_pRenderPass, m_pSwapChain, m_pImageView);

	m_pCommandPool = new ZwCommandPool();
	m_pCommandPool->init(m_pPhysicalDevice, m_pLogicalDevice, m_pSurface);

	m_pCommandBuffer = new ZwCommandBuffer();
	m_pCommandBuffer->init(m_pLogicalDevice, m_pCommandPool);

	m_pSynchronization = new ZwSynchronization();
	m_pSynchronization->init(m_pLogicalDevice);
}

void ZwRender::destroy()
{
	if (!m_pZwInstance || !m_pLogicalDevice || !m_pSurface || !m_pSwapChain || !m_pImageView || !m_pGraphicPipeline || !m_pRenderPass || !m_pFrameBuffers || !m_pCommandPool || !m_pSynchronization)
		return;

	m_pSynchronization->destroy(m_pLogicalDevice);
	m_pCommandPool->destroy(m_pLogicalDevice);
	m_pFrameBuffers->destroy(m_pLogicalDevice);
	m_pGraphicPipeline->destroy(m_pLogicalDevice);
	m_pRenderPass->destroy(m_pLogicalDevice);
	m_pImageView->destroy(m_pLogicalDevice);
	m_pSwapChain->destroy(m_pLogicalDevice);
	m_pLogicalDevice->destroy();
	m_pSurface->destroy(m_pZwInstance);

	if (ENABLEVALIDATIONLAYERS && m_pValidation)
		m_pValidation->destroy(m_pZwInstance);
	m_pZwInstance->destroy();

}

void ZwRender::drawFrame()
{
	// 等待上一帧完成
	vkWaitForFences(m_pLogicalDevice->getDeviceConst(), 1, &m_pSynchronization->getInFlightFence(), VK_TRUE, UINT64_MAX);
	vkResetFences(m_pLogicalDevice->getDeviceConst(), 1, &m_pSynchronization->getInFlightFence());

	// 从 swap chain 获取图像
	uint32_t imageIndex;
	vkAcquireNextImageKHR(m_pLogicalDevice->getDeviceConst(), m_pSwapChain->getSwapChain(), UINT64_MAX, m_pSynchronization->getImageAvailableSemaphore(), VK_NULL_HANDLE, &imageIndex);

	// 记录 command buffer
	vkResetCommandBuffer(m_pCommandBuffer->getCommandBuffer(), 0);
	m_pCommandBuffer->recordCommandBuffer(imageIndex, m_pRenderPass, m_pFrameBuffers, m_pGraphicPipeline, m_pSwapChain);

	// 提交 command buffer
	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	VkSemaphore waitSemaphores[] = { m_pSynchronization->getImageAvailableSemaphore() };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &m_pCommandBuffer->getCommandBuffer();
	VkSemaphore signalSemaphores[] = { m_pSynchronization->getRenderFinishedSemaphore() };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;
	if (vkQueueSubmit(m_pLogicalDevice->getGraphicsQueue(), 1, &submitInfo, m_pSynchronization->getInFlightFence()) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	// Presentation
	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;
	VkSwapchainKHR swapChains[] = { m_pSwapChain->getSwapChain() };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;
	vkQueuePresentKHR(m_pLogicalDevice->getPresentQueue(), &presentInfo);
}