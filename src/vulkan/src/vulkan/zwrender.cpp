#include <include/vulkan/zwrender.h>
#include <include/vulkan/zwinstance.h>
#include <include/vulkan/zwvalidation.h>
#include <include/vulkan/vulkanconst.h>
#include <include/vulkan/zwphysicaldevice.h>
#include <include/vulkan/zwlogicaldevice.h>
#include <include/vulkan/zwsurface.h>
#include <include/vulkan/zwswapchain.h>
#include <include/vulkan/zwgraphicpipeline.h>
#include <include/vulkan/zwrenderpass.h>
#include <include/vulkan/zwframebuffers.h>
#include <include/vulkan/zwsynchronization.h>
#include <include/vulkan/zwvertexbuffer.h>
#include <include/vulkan/zwindexbuffer.h>
#include <include/vulkan/zwrenderutils.h>
#include <include/vulkan/zwvulkanoption.h>
#include <include/vulkan/zwuniformbuffers.h>
#include <include/vulkan/zwtexturemanager.h>
#include <include/renderdata/zwvertex.h>
#include <include/renderdata/zwtexture.h>
#include <include/vulkan/zwdepthresources.h>
#include <include/vulkan/zwdescriptor.h>
#include <include/vulkan/zwcommandmanager.h>
#include <include/renderobject/zwrenderobjectmanager.h>
#include <stdexcept>

void ZwRender::init(GLFWwindow* pWindow, Scene* pScene)
{
	if (!pWindow || !pScene)
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

	m_pUniformBuffers = new ZwUniformBuffers();
	m_pUniformBuffers->init(m_pLogicalDevice, m_pPhysicalDevice);

	m_pCommandManager = new ZwCommandManager();
	m_pCommandManager->init(m_pPhysicalDevice, m_pLogicalDevice, m_pSurface);

	std::vector<ZwTexture> textures;
	textures.emplace_back(ZwTexture(VIKING_TEXTURE_PATH));
	textures.emplace_back(ZwTexture(TEAR_IMAGE_PATH));
	m_pTextureManager = new ZwTextureManager();
	m_pTextureManager->init(textures, m_pPhysicalDevice, m_pLogicalDevice, m_pCommandManager);

	m_pDescriptor = new ZwDescriptor();
	m_pDescriptor->init(m_pLogicalDevice, m_pUniformBuffers, m_pTextureManager);

	m_pRenderPass = new ZwRenderPass();
	m_pRenderPass->init(m_pLogicalDevice, m_pPhysicalDevice, m_pSwapChain);

	ShaderPath shaderPath{ VERTEXSHADERPATH, FRAGMENTSHADERPATH };
	m_pGraphicPipeline = new ZwGraphicPipeline();
	m_pGraphicPipeline->init({ shaderPath }, m_pLogicalDevice, m_pRenderPass, m_pDescriptor);

	m_DepthResources = new ZwDepthResources();
	m_DepthResources->init(m_pLogicalDevice, m_pPhysicalDevice, m_pSwapChain);

	m_pFrameBuffers = new ZwFrameBuffers();
	m_pFrameBuffers->init(m_pLogicalDevice, m_pRenderPass, m_pSwapChain, m_DepthResources);

	//ZwObj obj;
	//obj.load(VIKING_MODEL_PATH);
	//SingleVertexData testData1;
	//testData1.vertices = obj.vertices;
	//testData1.indices = obj.indices;

	//SingleVertexData testData2;
	//testData2.vertices = zwVertices;
	//testData2.indices = cubleIndices;

	const std::unordered_map<ElementId, std::shared_ptr<SurfaceMesh>>& meshes = pScene->getRenderMeshes();
	
	m_pObjectsManager = new ZwRenderObjectManager();
	m_pObjectsManager->prePareRenderObjects(m_pLogicalDevice, m_pPhysicalDevice, m_pCommandManager, /*{testData1, testData2}*/MeshConverter::parseVertexData(meshes));

	m_pSynchronization = new ZwSynchronization();
	m_pSynchronization->init(m_pLogicalDevice);
}

void ZwRender::destroy()
{
	if (!m_pZwInstance || !m_pLogicalDevice || !m_pSurface || !m_pGraphicPipeline || !m_pRenderPass  || !m_pSynchronization || !m_pObjectsManager ||!m_pDescriptor || !m_pUniformBuffers  || !m_pTextureManager)
		return;

	cleanUpSwapChain();
	m_pGraphicPipeline->destroy(m_pLogicalDevice);
	m_pUniformBuffers->destroy(m_pLogicalDevice);
	m_pDescriptor->destroy(m_pLogicalDevice);
	m_pTextureManager->destroy(m_pLogicalDevice);
	m_pObjectsManager->releaseObjects(m_pLogicalDevice);
	m_pRenderPass->destroy(m_pLogicalDevice);
	m_pSynchronization->destroy(m_pLogicalDevice);
	m_pCommandManager->destroy(m_pLogicalDevice);
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
	vkWaitForFences(m_pLogicalDevice->getDevice(), 1, &m_pSynchronization->getInFlightFence()[m_currentFrame], VK_TRUE, UINT64_MAX);

	// 从 swap chain 获取图像
	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(m_pLogicalDevice->getDevice(), m_pSwapChain->getSwapChain(), UINT64_MAX, m_pSynchronization->getImageAvailableSemaphore()[m_currentFrame], VK_NULL_HANDLE, &imageIndex);
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
	vkResetFences(m_pLogicalDevice->getDevice(), 1, &m_pSynchronization->getInFlightFence()[m_currentFrame]);

	UpdateUniformBufferEntry updateUniformBufferEntry;
	updateUniformBufferEntry.currentImage = m_currentFrame;
	updateUniformBufferEntry.pSwapChain = m_pSwapChain;
	updateUniformBufferEntry.pUniformBuffers = m_pUniformBuffers;
	ZwRenderUtils::updateUniformBuffer(updateUniformBufferEntry);

	// 记录 command buffer
	vkResetCommandBuffer(m_pCommandManager->getCommandBuffers()[m_currentFrame], 0);
	RecordCommandBufferEntry recordCommandBufferEntry;
	recordCommandBufferEntry.currentFrame = m_currentFrame;
	recordCommandBufferEntry.imageIndex = imageIndex;
	recordCommandBufferEntry.commandBuffer = m_pCommandManager->getCommandBuffers()[m_currentFrame];
	recordCommandBufferEntry.pRenderPass = m_pRenderPass;
	recordCommandBufferEntry.pFramebuffers = m_pFrameBuffers;
	recordCommandBufferEntry.pGraphicsPipeline = m_pGraphicPipeline;
	recordCommandBufferEntry.pSwapChain = m_pSwapChain;
	recordCommandBufferEntry.pObjectManager = m_pObjectsManager;
	recordCommandBufferEntry.pDescriptor = m_pDescriptor;
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
	submitInfo.pCommandBuffers = &m_pCommandManager->getCommandBuffers()[m_currentFrame];
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
	m_DepthResources->init(m_pLogicalDevice, m_pPhysicalDevice, m_pSwapChain);
	m_pFrameBuffers->init(m_pLogicalDevice, m_pRenderPass, m_pSwapChain, m_DepthResources);
}
void ZwRender::cleanUpSwapChain()
{
	if (!m_pFrameBuffers || !m_pSwapChain || !m_pLogicalDevice || !m_DepthResources)
		return;
	m_DepthResources->destroy(m_pLogicalDevice);
	m_pFrameBuffers->destroy(m_pLogicalDevice);
	m_pSwapChain->destroy(m_pLogicalDevice);
}

void ZwRender::setIsFramebufferResized(bool isResized)
{
	if (m_framebufferResized == isResized)
		return;
	m_framebufferResized = isResized;
}