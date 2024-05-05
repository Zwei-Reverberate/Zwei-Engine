#include <include/vulkan/zwswapchain.h>
#include <include/vulkan/zwswapchainsupportdetails.h>
#include <include/vulkan/zwqueuefamilyindices.h>
#include <stdexcept>
#include <algorithm> 

void ZwSwapChain::init(GLFWwindow* pWindow, ZwPhysicalDevice* pPhysicalDevice, ZwSurface* pSurface, ZwLogicalDevice* pLogicalDevice)
{
	if (!pWindow || !pPhysicalDevice || !pSurface || !pLogicalDevice)
		return;
	ZwSwapChainSupportDetails swapChainSupport = ZwSwapChainSupportDetails::querySwapChainSupport(pPhysicalDevice->getDeviceConst(), pSurface->getSurfaceConst());

    // 设置 swap chain 属性
    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities, pWindow);

    // 设定 swap chain 中的 image 数量
    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
    {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    // 填充创建的 createInfo
    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = pSurface->getSurfaceConst();
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1; // 指定每个 image 包含的层数
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; // 指定将使用 swap chain 中的 image 进行何种操作

    // 处理跨队列使用的 swap chain images
    ZwQueueFamilyIndices indices = ZwQueueFamilyIndices::findQueueFamilies(pPhysicalDevice->getDeviceConst(), pSurface->getSurfaceConst());
    uint32_t queueFamilyIndices[] = { indices.m_graphicsFamily.value(), indices.m_presentFamily.value() };
    if (indices.m_graphicsFamily != indices.m_presentFamily)
    {
        // image 由单个 queue family 所有
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else
    {
        // image 跨队列使用
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        // createInfo.queueFamilyIndexCount = 0; // Optional
        // createInfo.pQueueFamilyIndices = nullptr; // Optional
    }

    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;


    createInfo.oldSwapchain = VK_NULL_HANDLE;
    if (vkCreateSwapchainKHR(pLogicalDevice->getDeviceConst(), &createInfo, nullptr, &m_swapChain) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create swap chain!");
    }

    vkGetSwapchainImagesKHR(pLogicalDevice->getDeviceConst(), m_swapChain, &imageCount, nullptr);
    m_swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(pLogicalDevice->getDeviceConst(), m_swapChain, &imageCount, m_swapChainImages.data());
    m_swapChainImageFormat = surfaceFormat.format;
    m_swapChainExtent = extent;
}

void ZwSwapChain::destroy(ZwLogicalDevice* pLogicalDevice)
{
	if (!pLogicalDevice)
		return;
	vkDestroySwapchainKHR(pLogicalDevice->getDeviceConst(), m_swapChain, nullptr);
}

VkSurfaceFormatKHR ZwSwapChain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	for (const auto& availableFormat : availableFormats)
	{
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			return availableFormat;
		}
	}
	return availableFormats[0];
}

VkPresentModeKHR ZwSwapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
	// 优先使用 VK_PRESENT_MODE_MAILBOX_KHR，否则使用 VK_PRESENT_MODE_FIFO_KHR
	for (const auto& availablePresentMode : availablePresentModes)
	{
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			return availablePresentMode;
		}
	}
	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D ZwSwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* pWindow)
{
	if (!pWindow)
	{
		return VkExtent2D();
	}
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
	{
		return capabilities.currentExtent;
	}
	else
	{
		int width, height;
		glfwGetFramebufferSize(pWindow, &width, &height);

		VkExtent2D actualExtent =
		{
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};

		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

		return actualExtent;
	}
}
