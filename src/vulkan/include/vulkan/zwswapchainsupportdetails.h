#ifndef ZWSWAPCHAINSUPPORTDETAILS_H
#define ZWSWAPCHAINSUPPORTDETAILS_H
#include <include/vulkan/zwphysicaldevice.h>
#include <vector>

struct ZwSwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;

    static ZwSwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
};


#endif // !ZWSWAPCHAINSUPPORTDETAILS_H
