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
#include <include/vulkan/zwcommandbuffers.h>
#include <include/vulkan/zwsynchronization.h>
#include <include/vulkan/zwvertexbuffer.h>
#include <include/vulkan/zwindexbuffer.h>
#include <include/vulkan/zwrenderutils.h>
#include <include/vulkan/zwvulkanoption.h>
#include <include/vulkan/zwdescriptorsetlayout.h>
#include <include/vulkan/zwuniformbuffers.h>
#include <include/vulkan/zwdescriptorpool.h>
#include <include/vulkan/zwdescriptorsets.h>
#include <include/renderdata/zwvertex.h>
#include <stdexcept>

void ZwRender::init(GLFWwindow* pWindow)
{
	if (!pWindow)
		return;
	m_pWindow = pWindow;

	m_pZwInstance = new ZwInstance();
	m_pZwInstance->init();

	m_pSurface = new ZwSurface();
	m_pSurface->init(m_pZwInstance, m_pWindow);

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
	m_pSwapChain->init(m_pWindow, m_pPhysicalDevice, m_pSurface, m_pLogicalDevice);

	m_pImageView = new ZwImageView();
	m_pImageView->init(m_pSwapChain, m_pLogicalDevice);

	m_pRenderPass = new ZwRenderPass();
	m_pRenderPass->init(m_pLogicalDevice, m_pSwapChain);

	m_pDescriptorSetLayout = new ZwDescriptorSetLayout();
	m_pDescriptorSetLayout->init(m_pLogicalDevice);

	m_pGraphicPipeline = new ZwGraphicPipeline();
	m_pGraphicPipeline->init(VERTEXSHADERPATH, FRAGMENTSHADERPATH, m_pLogicalDevice, m_pRenderPass, m_pDescriptorSetLayout);

	m_pFrameBuffers = new ZwFrameBuffers();
	m_pFrameBuffers->init(m_pLogicalDevice, m_pRenderPass, m_pSwapChain, m_pImageView);

	m_pCommandPool = new ZwCommandPool();
	m_pCommandPool->init(m_pPhysicalDevice, m_pLogicalDevice, m_pSurface);

	m_pVertexBuffer = new ZwVertexBuffer();
	m_pVertexBuffer->init(m_pLogicalDevice, m_pPhysicalDevice, m_pCommandPool, zwVertices);

	m_pIndexBuffer = new ZwIndexBuffer();
	m_pIndexBuffer->init(m_pLogicalDevice, m_pPhysicalDevice, m_pCommandPool, zwIndices);

	m_pUniformBuffers = new ZwUniformBuffers();
	m_pUniformBuffers->init(m_pLogicalDevice, m_pPhysicalDevice);

	m_pDescriptorPool = new ZwDescriptorPool();
	m_pDescriptorPool->init(m_pLogicalDevice);

	m_pDescriptorSets = new ZwDescriptorSets();
	m_pDescriptorSets->init(m_pLogicalDevice, m_pDescriptorPool, m_pDescriptorSetLayout, m_pUniformBuffers);

	m_pCommandBuffers = new ZwCommandBuffers();
	m_pCommandBuffers->init(m_pLogicalDevice, m_pCommandPool);

	m_pSynchronization = new ZwSynchronization();
	m_pSynchronization->init(m_pLogicalDevice);
}

void ZwRender::destroy()
{
	if (!m_pZwInstance || !m_pLogicalDevice || !m_pSurface || !m_pGraphicPipeline || !m_pRenderPass || !m_pCommandPool || !m_pSynchronization || !m_pVertexBuffer || !m_pIndexBuffer ||!m_pDescriptorSetLayout || !m_pUniformBuffers || !m_pDescriptorPool)
		return;

	cleanUpSwapChain();
	m_pGraphicPipeline->destroy(m_pLogicalDevice);
	m_pUniformBuffers->destroy(m_pLogicalDevice);
	m_pDescriptorPool->destroy(m_pLogicalDevice);
	m_pDescriptorSetLayout->destroy(m_pLogicalDevice);
	m_pIndexBuffer->destroy(m_pLogicalDevice);
	m_pVertexBuffer->destroy(m_pLogicalDevice);
	m_pRenderPass->destroy(m_pLogicalDevice);
	m_pSynchronization->destroy(m_pLogicalDevice);
	m_pCommandPool->destroy(m_pLogicalDevice);
	m_pLogicalDevice->destroy();
	m_pSurface->destroy(m_pZwInstance);

	if (ENABLEVALIDATIONLAYERS && m_pValidation)
		m_pValidation->destroy(m_pZwInstance);
	m_pZwInstance->destroy();

}

void ZwRender::waitIdle()
{
	if (!m_pLogicalDevice)
		return;
	m_pLogicalDevice->waitIdle();
}

void ZwRender::drawFrame()
{
	// 等待上一帧完成
	vkWaitForFences(m_pLogicalDevice->getDeviceConst(), 1, &m_pSynchronization->getInFlightFence()[m_currentFrame], VK_TRUE, UINT64_MAX);

	// 从 swap chain 获取图像
	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(m_pLogicalDevice->getDeviceConst(), m_pSwapChain->getSwapChain(), UINT64_MAX, m_pSynchronization->getImageAvailableSemaphore()[m_currentFrame], VK_NULL_HANDLE, &imageIndex);
	if (result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		recreateSwapChain();
		return;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
	{
		throw std::runtime_error("failed to acquire swap chain image!");
	}
	// Only reset the fence if we are submitting work
	vkResetFences(m_pLogicalDevice->getDeviceConst(), 1, &m_pSynchronization->getInFlightFence()[m_currentFrame]);


	UpdateUniformBufferEntry updateUniformBufferEntry;
	updateUniformBufferEntry.currentImage = m_currentFrame;
	updateUniformBufferEntry.pSwapChain = m_pSwapChain;
	updateUniformBufferEntry.pUniformBuffers = m_pUniformBuffers;
	ZwRenderUtils::updateUniformBuffer(updateUniformBufferEntry);

	// 记录 command buffer
	vkResetCommandBuffer(m_pCommandBuffers->getCommandBuffers()[m_currentFrame], 0);
	RecordCommandBufferEntry recordCommandBufferEntry;
	recordCommandBufferEntry.currentFrame = m_currentFrame;
	recordCommandBufferEntry.imageIndex = imageIndex;
	recordCommandBufferEntry.commandBuffer = m_pCommandBuffers->getCommandBuffers()[m_currentFrame];
	recordCommandBufferEntry.pRenderPass = m_pRenderPass;
	recordCommandBufferEntry.pFramebuffers = m_pFrameBuffers;
	recordCommandBufferEntry.pGraphicsPipeline = m_pGraphicPipeline;
	recordCommandBufferEntry.pSwapChain = m_pSwapChain;
	recordCommandBufferEntry.pVertexBuffer = m_pVertexBuffer;
	recordCommandBufferEntry.pIndexBuffer = m_pIndexBuffer;
	recordCommandBufferEntry.pDescriptorSets = m_pDescriptorSets;
	ZwRenderUtils::recordCommandBuffer(recordCommandBufferEntry);

	// 提交 command buffer
	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	VkSemaphore waitSemaphores[] = { m_pSynchronization->getImageAvailableSemaphore()[m_currentFrame]};
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &m_pCommandBuffers->getCommandBuffers()[m_currentFrame];
	VkSemaphore signalSemaphores[] = { m_pSynchronization->getRenderFinishedSemaphore()[m_currentFrame]};
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;
	if (vkQueueSubmit(m_pLogicalDevice->getGraphicsQueue(), 1, &submitInfo, m_pSynchronization->getInFlightFence()[m_currentFrame]) != VK_SUCCESS)
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
	result = vkQueuePresentKHR(m_pLogicalDevice->getPresentQueue(), &presentInfo);
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || getFramebufferResized())
	{
		setIsFramebufferResized(false);
		recreateSwapChain();
	}
	else if (result != VK_SUCCESS)
	{
		throw std::runtime_error("failed to present swap chain image!");
	}

	// 每次都前进到下一帧
	m_currentFrame = (m_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}


void ZwRender::recreateSwapChain()
{
	if (!m_pWindow || !m_pLogicalDevice)
		return;

	// 重新创建 swap chain
	int width = 0, height = 0;
	glfwGetFramebufferSize(m_pWindow, &width, &height);
	while (width == 0 || height == 0) // 处理窗口最小化的情况
	{
		glfwGetFramebufferSize(m_pWindow, &width, &height);
		glfwWaitEvents();
	}
	m_pLogicalDevice->waitIdle(); // 不应触及仍在使用的资源
	cleanUpSwapChain();
	m_pSwapChain->init(m_pWindow, m_pPhysicalDevice, m_pSurface, m_pLogicalDevice);
	m_pImageView->init(m_pSwapChain, m_pLogicalDevice);
	m_pFrameBuffers->init(m_pLogicalDevice, m_pRenderPass, m_pSwapChain, m_pImageView);
}
void ZwRender::cleanUpSwapChain()
{
	if (!m_pFrameBuffers || !m_pImageView || !m_pSwapChain || !m_pLogicalDevice)
		return;
	m_pFrameBuffers->destroy(m_pLogicalDevice);
	m_pImageView->destroy(m_pLogicalDevice);
	m_pSwapChain->destroy(m_pLogicalDevice);
}

void ZwRender::setIsFramebufferResized(bool isResized)
{
	if (m_framebufferResized == isResized)
		return;
	m_framebufferResized = isResized;
}