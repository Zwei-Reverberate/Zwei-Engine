#ifndef ZWPHYSICALDEVICE_H
#define ZWPHYSICALDEVICE_H
#include<include/vulkan/zwinstance.h>

class ZwSurface;
class ZwPhysicalDevice
{
public:
	void init(const ZwInstance* pInstance, const ZwSurface* pSurface);
	const VkPhysicalDevice& getDeviceConst() const { return m_PhysicalDevice; }

private:
	VkPhysicalDevice m_PhysicalDevice = nullptr;
};

#endif