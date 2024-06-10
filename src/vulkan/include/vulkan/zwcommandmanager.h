#ifndef ZWCOMMANDMANAGER_H
#define ZWCOMMANDMANAGER_H
#include <include/vulkan/zwlogicaldevice.h>
#include <vector>

class ZwSurface;
class ZwCommandManager
{
public:
	void init(ZwPhysicalDevice* pPhysicalDevice, ZwLogicalDevice* pLogicalDevice, ZwSurface* pSurface);
	void destroy(ZwLogicalDevice* pLogicalDevice);

	const VkCommandPool& getCommandPool() const { return m_commandPool; }
	const std::vector<VkCommandBuffer>& getCommandBuffers() const { return m_commandBuffers; }

private:
	VkCommandPool m_commandPool;
	std::vector<VkCommandBuffer> m_commandBuffers;
};

#endif // !ZWCOMMAND_H
