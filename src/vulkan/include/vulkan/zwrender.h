#ifndef ZWRENDER_H
#define	ZWRENDER_H
#include <include/vulkan/zwinstance.h>

class ZwValidation;
class ZwPhysicalDevice;
class ZwLogicalDevice;
class ZwSurface;
class ZwSwapChain;
class ZwImageView;
class ZwRenderPass;
class ZwGraphicPipeline;
class ZwFrameBuffers;
class ZwCommandPool;
class ZwCommandBuffer;
class ZwSynchronization;
class ZwRender
{
public:
	void init(GLFWwindow* pWindow);
	void destroy();
	void drawFrame();

private:
	ZwInstance* m_pZwInstance = nullptr;
	ZwValidation* m_pValidation = nullptr; 
	ZwPhysicalDevice* m_pPhysicalDevice = nullptr;
	ZwLogicalDevice* m_pLogicalDevice = nullptr;
	ZwSurface* m_pSurface = nullptr;
	ZwSwapChain* m_pSwapChain = nullptr;
	ZwImageView* m_pImageView = nullptr;
	ZwRenderPass* m_pRenderPass = nullptr;
	ZwGraphicPipeline* m_pGraphicPipeline = nullptr;
	ZwFrameBuffers* m_pFrameBuffers = nullptr;
	ZwCommandPool* m_pCommandPool = nullptr;
	ZwCommandBuffer* m_pCommandBuffer = nullptr;
	ZwSynchronization* m_pSynchronization = nullptr;
};

#endif // !ZWRENDER_H
