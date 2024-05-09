#include <include/vulkan/zwframebuffers.h>
#include <include/vulkan/zwrenderpass.h>
#include <include/vulkan/zwframebuffers.h>
#include <include/vulkan/zwswapchain.h>
#include <include/vulkan/zwimageview.h>
#include <stdexcept>

void ZwFrameBuffers::init(ZwLogicalDevice* pLogicalDevice, ZwRenderPass* pRenderPass, ZwSwapChain* pSwapChain, ZwImageView* pImageView)
{
	if (!pLogicalDevice || !pRenderPass || !pSwapChain)
		return;

    const std::vector<VkImageView>& swapChainImageViews = pImageView->getSwapChainImageViews();
    m_swapChainFramebuffers.resize(swapChainImageViews.size());

    // 为 swap chain 的每一个 image view 创建对应的 framebuffer
    for (size_t i = 0; i < pSwapChain->getSwapChainImages().size(); i++)
    {
        VkImageView attachments[] =
        {
            swapChainImageViews[i]
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = pRenderPass->getRenderPass();
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = pSwapChain->getSwapChainExtent().width;
        framebufferInfo.height = pSwapChain->getSwapChainExtent().height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(pLogicalDevice->getDeviceConst(), &framebufferInfo, nullptr, &m_swapChainFramebuffers[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}

void ZwFrameBuffers::destroy(ZwLogicalDevice* pLogicalDevice)
{
    if (!pLogicalDevice)
        return;
    for (auto& frameBuffer : m_swapChainFramebuffers)
    {
        vkDestroyFramebuffer(pLogicalDevice->getDeviceConst(), frameBuffer, nullptr);
    }
}