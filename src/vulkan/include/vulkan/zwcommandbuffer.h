#ifndef ZWCOMMANDBUFFER_H
#define ZWCOMMANDBUFFER_H
#include <include/vulkan/zwlogicaldevice.h>

class ZwCommandPool;
class ZwRenderPass;
class ZwFrameBuffers;
class ZwGraphicPipeline;
class ZwSwapChain;
class ZwCommandBuffer
{
public:
	void init(ZwLogicalDevice* pLogicalDevice, ZwCommandPool* pCommandPool);
	void recordCommandBuffer(uint32_t imageIndex, ZwRenderPass* pRenderPass, ZwFrameBuffers* pFramebuffers, ZwGraphicPipeline* pGraphicsPipeline, ZwSwapChain* pSwapChain);
	const VkCommandBuffer& getCommandBuffer() const { return m_commandBuffer; }

private:
	VkCommandBuffer m_commandBuffer;
};

#endif // !ZWCOMMANDBUFFER_H
