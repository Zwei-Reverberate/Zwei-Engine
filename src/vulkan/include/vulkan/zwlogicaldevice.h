#ifndef ZWLOGICALDEVICE_H
#define ZWLOGICALDEVICE_H
#include <include/vulkan/zwphysicaldevice.h>

class ZwLogicalDevice
{
public:
	void init(const ZwPhysicalDevice* pPhysicalDevice);
	void destroy();

private:
	VkDevice m_device;
	VkQueue m_graphicsQueue;
};

#endif // !ZWLOGICALDEVICE_H
