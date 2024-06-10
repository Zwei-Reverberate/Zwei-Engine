#ifndef ZWFRAMEBUFFERS_H
#define ZWFRAMEBUFFERS_H
#include <include/vulkan/zwlogicaldevice.h>
#include <vector>

class ZwRenderPass;
class ZwSwapChain;
class ZwDepthResources;
class ZwImageView;

class ZwFrameBuffers
{
public:
	void init(ZwLogicalDevice* pLogicalDevice, ZwRenderPass* pRenderPass, ZwSwapChain* pSwapChain, ZwDepthResources* pDepthResources);
	void destroy(ZwLogicalDevice* pLogicalDevice);
	const std::vector<VkFramebuffer>& getFrameBuffers() const { return m_swapChainFramebuffers; }

private:
	std::vector<VkFramebuffer> m_swapChainFramebuffers;
};
#endif // !ZWFRAMEBUFFERS_H
