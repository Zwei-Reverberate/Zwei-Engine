#ifndef ZWSWAPCHAIN_H
#define ZWSWAPCHAIN_H
#include <include/vulkan/zwlogicaldevice.h>
#include <include/vulkan/zwsurface.h>
#include <vector>

class ZwSwapChain
{
public:
	void init(GLFWwindow* pWindow, ZwPhysicalDevice* pPhysicalDevice, ZwSurface* pSurface, ZwLogicalDevice* pLogicalDevice);
	void destroy(ZwLogicalDevice* pLogicalDevice);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* pWindow);

	const VkSwapchainKHR& getSwapChain() const { return m_swapChain; }
	const std::vector<VkImage>& getSwapChainImages() const { return m_swapChainImages; }
	const VkFormat& getSwapChainImageFormat() const { return m_swapChainImageFormat; }
	const VkExtent2D& getSwapChainExtent() const { return m_swapChainExtent; }

private:
	VkSwapchainKHR m_swapChain = nullptr;
	std::vector<VkImage> m_swapChainImages;
	VkFormat m_swapChainImageFormat;
	VkExtent2D m_swapChainExtent;
};

#endif // !ZWSWAPCHAIN_H
