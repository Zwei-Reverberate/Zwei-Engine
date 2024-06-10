#ifndef ZWRENDER_H
#define	ZWRENDER_H
#include <include/vulkan/zwinstance.h>
#include <GLFW/glfw3.h>

class ZwValidation;
class ZwPhysicalDevice;
class ZwLogicalDevice;
class ZwSurface;
class ZwSwapChain;
class ZwRenderPass;
class ZwGraphicPipeline;
class ZwFrameBuffers;
class ZwCommandManager;
class ZwSynchronization;
class ZwVertexBuffer;
class ZwIndexBuffer;
class ZwUniformBuffers;
class ZwTextureManager;
class ZwDepthResources;
class ZwDescriptor;
class ZwRender
{
public:
	void init(GLFWwindow* pWindow);
	void destroy();
	void drawFrame();
	void waitIdle();
	bool getFramebufferResized() const { return m_framebufferResized; }
	void setIsFramebufferResized(bool isResized);

private:
	void recreateSwapChain();
	void cleanUpSwapChain();

private:
	ZwInstance* m_pZwInstance = nullptr;
	ZwValidation* m_pValidation = nullptr; 
	ZwPhysicalDevice* m_pPhysicalDevice = nullptr;
	ZwLogicalDevice* m_pLogicalDevice = nullptr;
	ZwSurface* m_pSurface = nullptr;
	ZwSwapChain* m_pSwapChain = nullptr;
	ZwRenderPass* m_pRenderPass = nullptr;
	ZwGraphicPipeline* m_pGraphicPipeline = nullptr;
	ZwFrameBuffers* m_pFrameBuffers = nullptr;
	ZwCommandManager* m_pCommandManager = nullptr;
	ZwSynchronization* m_pSynchronization = nullptr;
	ZwVertexBuffer* m_pVertexBuffer = nullptr;
	ZwIndexBuffer* m_pIndexBuffer = nullptr;
	ZwUniformBuffers* m_pUniformBuffers = nullptr;
	ZwDescriptor* m_pDescriptor = nullptr;
	ZwTextureManager* m_pTextureManager = nullptr;
	ZwDepthResources* m_DepthResources = nullptr;
	uint32_t m_currentFrame = 0;

	// temp
	GLFWwindow* m_pWindow = nullptr;
	bool m_framebufferResized = false;
};

#endif // !ZWRENDER_H
