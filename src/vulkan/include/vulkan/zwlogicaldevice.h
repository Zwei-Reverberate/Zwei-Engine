#ifndef ZWLOGICALDEVICE_H
#define ZWLOGICALDEVICE_H
#include <include/vulkan/zwphysicaldevice.h>

class ZwSurface;
class ZwLogicalDevice
{
public:
	void init(const ZwPhysicalDevice* pPhysicalDevice, const ZwSurface* pSurface);
	void destroy();
	void waitIdle();
	const VkDevice& getDeviceConst() const { return m_device; }
	const VkQueue& getGraphicsQueue() const { return m_graphicsQueue; }
	const VkQueue& getPresentQueue() const { return m_presentQueue; }

private:
	VkDevice m_device = nullptr;
	VkQueue m_graphicsQueue;
	VkQueue m_presentQueue;
};

#endif // !ZWLOGICALDEVICE_H
