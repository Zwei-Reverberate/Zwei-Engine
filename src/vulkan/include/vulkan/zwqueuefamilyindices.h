#ifndef ZWQUEUEFAMILYINDICES_H
#define ZWQUEUEFAMILYINDICES_H
#include <include/vulkan/zwphysicaldevice.h>
#include <optional>

class ZwQueueFamilyIndices
{
public:
	static ZwQueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	static bool isDeviceSuitable(VkPhysicalDevice device);

public:
	bool isComplete();

public:
	std::optional<uint32_t> m_graphicsFamily;
};


#endif // !ZWQUEUEFAMILYINDICES_H
