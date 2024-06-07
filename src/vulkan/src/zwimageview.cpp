#include <include/vulkan/zwimageview.h>
#include <include/vulkan/zwswapchain.h>
#include <include/vulkan/zwrenderutils.h>
#include <stdexcept>

void ZwImageView::init(ZwSwapChain* pSwapChain, ZwLogicalDevice* pLogicalDevice)
{
	if (!pSwapChain || !pLogicalDevice)
		return;
    std::vector<VkImage> swapChainImages = pSwapChain->getSwapChainImages();
    m_swapChainImageViews.resize(swapChainImages.size());
    for (size_t i = 0; i < swapChainImages.size(); i++)
    {
        CreateImageViewEntry createImageVeiwEntry;
        createImageVeiwEntry.format = pSwapChain->getSwapChainImageFormat();
        createImageVeiwEntry.image = swapChainImages[i];
        createImageVeiwEntry.pLogicalDevice = pLogicalDevice;

        m_swapChainImageViews[i] = ZwRenderUtils::createImageView(createImageVeiwEntry);
        if (!m_swapChainImageViews[i])
            continue;
    }
}

void ZwImageView::destroy(ZwLogicalDevice* pLogicalDevice)
{
    if (!pLogicalDevice)
        return;
    for (auto imageView : m_swapChainImageViews)
    {
        vkDestroyImageView(pLogicalDevice->getDeviceConst(), imageView, nullptr);
    }
}
