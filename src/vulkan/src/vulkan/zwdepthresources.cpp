#include <include/vulkan/zwdepthresources.h>
#include <include/vulkan/zwrenderutils.h>
#include <include/vulkan/zwswapchain.h>


void ZwDepthResources::init(ZwLogicalDevice* pLogicalDevice, ZwPhysicalDevice* pPhysicalDevice, ZwSwapChain* pSwapChain)
{
	if (!pLogicalDevice || !pPhysicalDevice || !pSwapChain)
		return;

	VkFormat depthFormat = ZwRenderUtils::findDepthFormat(pPhysicalDevice->getDevice());

	CreateImageEntry createImageEntry;
	createImageEntry.width = pSwapChain->getSwapChainExtent().width;
	createImageEntry.height = pSwapChain->getSwapChainExtent().height;
	createImageEntry.format = depthFormat;
	createImageEntry.tiling = VK_IMAGE_TILING_OPTIMAL;
	createImageEntry.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
	createImageEntry.properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
	createImageEntry.pLogicalDevice = pLogicalDevice;
	createImageEntry.pPhysicalDevice = pPhysicalDevice;

	CreateImageResult createImageRes = ZwRenderUtils::createImage(createImageEntry);
	if (!createImageRes.sucess)
		return;
	m_depthImage = createImageRes.image;
	m_depthImageMemory = createImageRes.imageMemory;

	CreateImageViewEntry createImageViewEntry;
	createImageViewEntry.image = m_depthImage;
	createImageViewEntry.format = depthFormat;
	createImageViewEntry.aspectFlags = VK_IMAGE_ASPECT_DEPTH_BIT;
	createImageViewEntry.pLogicalDevice = pLogicalDevice;

	m_depthImageView = ZwRenderUtils::createImageView(createImageViewEntry);

	// transitionImageLayout https://vulkan-tutorial.com/Depth_buffering
}


void ZwDepthResources::destroy(ZwLogicalDevice* pLogicalDevice)
{
	if (!pLogicalDevice)
		return;
	vkDestroyImageView(pLogicalDevice->getDevice(), m_depthImageView, nullptr);
	vkDestroyImage(pLogicalDevice->getDevice(), m_depthImage, nullptr);
	vkFreeMemory(pLogicalDevice->getDevice(), m_depthImageMemory, nullptr);
}
