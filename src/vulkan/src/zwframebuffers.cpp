#include <include/vulkan/zwframebuffers.h>
#include <include/vulkan/zwrenderpass.h>
#include <include/vulkan/zwframebuffers.h>
#include <include/vulkan/zwswapchain.h>
#include <include/vulkan/zwdepthresources.h>
#include <array>
#include <stdexcept>

void ZwFrameBuffers::init(ZwLogicalDevice* pLogicalDevice, ZwRenderPass* pRenderPass, ZwSwapChain* pSwapChain, ZwDepthResources* pDepthResources)
{
	if (!pLogicalDevice || !pRenderPass || !pSwapChain || !pDepthResources)
		return;

    const std::vector<VkImageView>& swapChainImageViews = pSwapChain->getSwapChainImageViews();
    m_swapChainFramebuffers.resize(swapChainImageViews.size());

    // 为 swap chain 的每一个 image view 创建对应的 framebuffer
    for (size_t i = 0; i < pSwapChain->getSwapChainImages().size(); i++)
    {
        std::array<VkImageView, 2> attachments =
        {
            swapChainImageViews[i],
            pDepthResources->getDepthImageView()
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = pRenderPass->getRenderPass();
        framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        framebufferInfo.pAttachments = attachments.data();
        framebufferInfo.width = pSwapChain->getSwapChainExtent().width;
        framebufferInfo.height = pSwapChain->getSwapChainExtent().height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(pLogicalDevice->getDevice(), &framebufferInfo, nullptr, &m_swapChainFramebuffers[i]) != VK_SUCCESS)
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
        vkDestroyFramebuffer(pLogicalDevice->getDevice(), frameBuffer, nullptr);
    }
}