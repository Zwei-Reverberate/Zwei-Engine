#ifndef ZWQUEUEFAMILYINDICES_H
#define ZWQUEUEFAMILYINDICES_H
#include <include/vulkan/zwphysicaldevice.h>
#include <optional>

class ZwQueueFamilyIndices
{
public:
	static ZwQueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
	static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
	static bool checkDeviceExtensionSupport(VkPhysicalDevice device);

public:
	bool isComplete();

public:
	std::optional<uint32_t> m_graphicsFamily;
	std::optional<uint32_t> m_presentFamily;
};


#endif // !ZWQUEUEFAMILYINDICES_H
