#ifndef ZWCOMMANDPOOL_H
#define ZWCOMMANDPOOL_H
#include <include/vulkan/zwlogicaldevice.h>

class ZwPhysicalDevice;
class ZwSurface;
class ZwCommandPool
{
public:
	void init(ZwPhysicalDevice* pPhysicalDevice, ZwLogicalDevice* pLogicalDevice, ZwSurface* pSurface);
	void destroy(ZwLogicalDevice* pLogicalDevice);
	const VkCommandPool& getCommandPool() const { return m_commandPool; }
private:
	VkCommandPool m_commandPool;
};

#endif // !ZWCOMMANDPOOL_H