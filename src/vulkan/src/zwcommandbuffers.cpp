#include <include/vulkan/zwcommandbuffers.h>
#include <include/vulkan/zwcommandpool.h>
#include <include/vulkan/zwrenderpass.h>
#include <include/vulkan/zwframebuffers.h>
#include <include/vulkan/zwgraphicpipeline.h>
#include <include/vulkan/zwswapchain.h>
#include <include/vulkan/vulkanconst.h>
#include <stdexcept>

void ZwCommandBuffers::init(ZwLogicalDevice* pLogicalDevice, ZwCommandPool* pCommandPool)
{
	if (!pLogicalDevice || !pCommandPool)
		return;

    m_commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = pCommandPool->getCommandPool(); // 指定 commandPool
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY; // 指定是主 command buffer 还是辅助 command buffer，此处是主 command buffer
    allocInfo.commandBufferCount = (uint32_t)m_commandBuffers.size();; // 指定分配的数量

    if (vkAllocateCommandBuffers(pLogicalDevice->getDeviceConst(), &allocInfo, m_commandBuffers.data()) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

void ZwCommandBuffers::recordCommandBuffer(uint32_t imageIndex, VkCommandBuffer commandBuffer, ZwRenderPass* pRenderPass, ZwFrameBuffers* pFramebuffers, ZwGraphicPipeline* pGraphicsPipeline, ZwSwapChain* pSwapChain)
{
    if (!pRenderPass || !pFramebuffers || !pGraphicsPipeline || !pSwapChain || !commandBuffer)
        return;

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = pRenderPass->getRenderPass();
    renderPassInfo.framebuffer = pFramebuffers->getFrameBuffers()[imageIndex];
    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = pSwapChain->getSwapChainExtent();

    VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;
    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pGraphicsPipeline->getGraphicsPipeline());
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)pSwapChain->getSwapChainExtent().width;
    viewport.height = (float)pSwapChain->getSwapChainExtent().height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = pSwapChain->getSwapChainExtent();
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

    vkCmdDraw(commandBuffer, 3, 1, 0, 0);
    vkCmdEndRenderPass(commandBuffer);
    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to record command buffer!");
    }
}
