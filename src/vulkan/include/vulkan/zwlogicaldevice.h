#ifndef ZWLOGICALDEVICE_H
#define ZWLOGICALDEVICE_H
#include <include/vulkan/zwphysicaldevice.h>

class ZwSurface;
class ZwLogicalDevice
{
public:
	void init(const ZwPhysicalDevice* pPhysicalDevice, const ZwSurface* pSurface);
	void destroy();
	const VkDevice& getDeviceConst() const { return m_device; }

private:
	VkDevice m_device;
	VkQueue m_graphicsQueue;
	VkQueue m_presentQueue;
};

#endif // !ZWLOGICALDEVICE_H
