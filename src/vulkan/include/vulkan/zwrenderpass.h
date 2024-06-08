#ifndef ZWRENDERPASS_H
#define ZWRENDERPASS_H
#include <include/vulkan/zwlogicaldevice.h>

class ZwSwapChain;
class ZwRenderPass
{
public:
	void init(ZwLogicalDevice* pLogicalDevice, ZwPhysicalDevice* pPhysicalDevice, ZwSwapChain* pSwapChain);
	void destroy(ZwLogicalDevice* pLogicalDevice);
	const VkRenderPass& getRenderPass() const { return m_renderPass; }

private:
	VkRenderPass m_renderPass;
};

#endif // !ZWRENDERPASS_H
