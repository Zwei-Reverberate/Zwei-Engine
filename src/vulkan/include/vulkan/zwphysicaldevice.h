#ifndef ZWPHYSICALDEVICE_H
#define ZWPHYSICALDEVICE_H
#include<include/vulkan/zwinstance.h>

class ZwPhysicalDevice
{
public:
	void init(const ZwInstance* pInstance);
	const VkPhysicalDevice& getDeviceConst() const { return m_PhysicalDevice; }

private:
	VkPhysicalDevice m_PhysicalDevice = nullptr;
};

#endif