#include <include/vulkan/zwqueuefamilyindices.h>
#include<vector>

bool ZwQueueFamilyIndices::isComplete()
{
	return m_graphicsFamily.has_value();
}

ZwQueueFamilyIndices ZwQueueFamilyIndices::findQueueFamilies(VkPhysicalDevice device)
{
    ZwQueueFamilyIndices  indices;
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies)
    {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) // 寻找一个支持图形 commands 的 queue family
        {
            indices.m_graphicsFamily = i;
        }

        if (indices.isComplete())
        {
            break;
        }
        i++;
    }
    return indices;
}

bool ZwQueueFamilyIndices::isDeviceSuitable(VkPhysicalDevice device)
{
    ZwQueueFamilyIndices  indices = ZwQueueFamilyIndices::findQueueFamilies(device);
    return indices.isComplete();
}