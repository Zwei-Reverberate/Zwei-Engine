#ifndef ZWCOMMANDBUFFERS_H
#define ZWCOMMANDBUFFERS_H
#include <include/vulkan/zwlogicaldevice.h>
#include <vector>

class ZwCommandPool;
class ZwRenderPass;
class ZwFrameBuffers;
class ZwGraphicPipeline;
class ZwSwapChain;
class ZwVertexBuffer;
class ZwIndexBuffer;
class ZwCommandBuffers
{
public:
	void init(ZwLogicalDevice* pLogicalDevice, ZwCommandPool* pCommandPool);
	const std::vector<VkCommandBuffer>& getCommandBuffers() const { return m_commandBuffers; }

private:
	std::vector<VkCommandBuffer> m_commandBuffers;
};

#endif // !ZWCOMMANDBUFFERS_H
