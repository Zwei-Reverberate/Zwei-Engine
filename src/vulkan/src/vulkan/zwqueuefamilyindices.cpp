#include <include/vulkan/zwqueuefamilyindices.h>
#include <include/vulkan/vulkanconst.h>
#include <include/vulkan/zwswapchainsupportdetails.h>
#include <vector>
#include <set>
#include <string>

bool ZwQueueFamilyIndices::isComplete()
{
	return m_graphicsFamily.has_value();
}

ZwQueueFamilyIndices ZwQueueFamilyIndices::findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface)
{
    ZwQueueFamilyIndices  indices;
    if (!device || !surface)
        return indices;

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

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
        if (presentSupport)
        {
            indices.m_presentFamily = i;
        }

        if (indices.isComplete())
        {
            break;
        }
        i++;
    }
    return indices;
}

bool ZwQueueFamilyIndices::isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface)
{
    if (!device || !surface)
        return false;

    ZwQueueFamilyIndices  indices = ZwQueueFamilyIndices::findQueueFamilies(device, surface);
    bool extensionsSupported = checkDeviceExtensionSupport(device);

    VkPhysicalDeviceFeatures supportedFeatures;
    vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

    bool swapChainAdequate = false;
    if (extensionsSupported)
    {
        ZwSwapChainSupportDetails swapChainSupport = ZwSwapChainSupportDetails::querySwapChainSupport(device, surface);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }
    return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
}

bool ZwQueueFamilyIndices::checkDeviceExtensionSupport(VkPhysicalDevice device)
{
    if (!device)
        return false;

    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(DEVICE_EXTENSIONS.begin(), DEVICE_EXTENSIONS.end());

    for (const auto& extension : availableExtensions)
    {
        requiredExtensions.erase(extension.extensionName);
    }
    return requiredExtensions.empty();
}