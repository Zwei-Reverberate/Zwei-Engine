#include <include/vulkan/zwrenderutils.h>
#include <include/renderdata/zwvertex.h>
#include <include/vulkan/zwcommandpool.h>
#include <include/vulkan/zwframebuffers.h>
#include <include/vulkan/zwrenderpass.h>
#include <include/vulkan/zwgraphicpipeline.h>
#include <include/vulkan/zwswapchain.h>
#include <include/vulkan/zwvertexbuffer.h>
#include <include/vulkan/zwindexbuffer.h>
#include <stdexcept>

VkVertexInputBindingDescription ZwRenderUtils::getBindingDescription()
{
    VkVertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0; // 现在的顶点数据都打包在一个数组中，因此只有一个绑定
    bindingDescription.stride = sizeof(ZwVertex); // 指定从一个条目到下一个条目的字节数
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX; // 暂未使用实例化渲染
    return bindingDescription;
}

std::array<VkVertexInputAttributeDescription, 2> ZwRenderUtils::getAttributeDescriptions()
{
    std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
    attributeDescriptions[0].binding = 0; // 告诉 Vulkan 每个顶点数据来自哪个绑定
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions[0].offset = ZwVertex::getPosOffset();

    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[1].offset = ZwVertex::getColorOffset();

    return attributeDescriptions;
}


uint32_t ZwRenderUtils::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, ZwPhysicalDevice* pPhysicalDevice)
{
    if (!pPhysicalDevice)
        return uint32_t();
    VkPhysicalDeviceMemoryProperties memProperties; // 查询可用的内存类型信息
    vkGetPhysicalDeviceMemoryProperties(pPhysicalDevice->getDeviceConst(), &memProperties);
    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
            return i;
    }
    throw std::runtime_error("failed to find suitable memory type!");
}


CreateBufferResult ZwRenderUtils::createBuffer(const CreateBufferEntry& entry)
{
    CreateBufferResult result;

    if (!entry.pLogicalDevice || !entry.pPhysicalDevice)
        return result;

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = entry.size;
    bufferInfo.usage = entry.usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(entry.pLogicalDevice->getDeviceConst(), &bufferInfo, nullptr, &result.buffer) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(entry.pLogicalDevice->getDeviceConst(), result.buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, entry.properties, entry.pPhysicalDevice);

    if (vkAllocateMemory(entry.pLogicalDevice->getDeviceConst(), &allocInfo, nullptr, &result.bufferMemory) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    vkBindBufferMemory(entry.pLogicalDevice->getDeviceConst(), result.buffer, result.bufferMemory, 0);

    result.sucess = true;
    return result;
}


void ZwRenderUtils::copyBuffer(const CopyBufferEntry& entry)
{
    if (!entry.pLogicalDevice || !entry.pCommandPool)
        return;

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = entry.pCommandPool->getCommandPool();
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(entry.pLogicalDevice->getDeviceConst(), &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    VkBufferCopy copyRegion{};
    copyRegion.size = entry.size;
    vkCmdCopyBuffer(commandBuffer, entry.srcBuffer, entry.dstBuffer, 1, &copyRegion);

    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(entry.pLogicalDevice->getGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(entry.pLogicalDevice->getGraphicsQueue());

    vkFreeCommandBuffers(entry.pLogicalDevice->getDeviceConst(), entry.pCommandPool->getCommandPool(), 1, &commandBuffer);
}


void ZwRenderUtils::recordCommandBuffer(const RecordCommandBufferEntry& entry)
{
    if (!entry.pFramebuffers || !entry.pGraphicsPipeline || !entry.pIndexBuffer || !entry.pRenderPass || !entry.pSwapChain || !entry.pVertexBuffer)
        return;

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    if (vkBeginCommandBuffer(entry.commandBuffer, &beginInfo) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = entry.pRenderPass->getRenderPass();
    renderPassInfo.framebuffer = entry.pFramebuffers->getFrameBuffers()[entry.imageIndex];
    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = entry.pSwapChain->getSwapChainExtent();

    VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;
    vkCmdBeginRenderPass(entry.commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(entry.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, entry.pGraphicsPipeline->getGraphicsPipeline());
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)entry.pSwapChain->getSwapChainExtent().width;
    viewport.height = (float)entry.pSwapChain->getSwapChainExtent().height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(entry.commandBuffer, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = entry.pSwapChain->getSwapChainExtent();
    vkCmdSetScissor(entry.commandBuffer, 0, 1, &scissor);

    VkBuffer vertexBuffers[] = { entry.pVertexBuffer->getVertexBuffer() };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(entry.commandBuffer, 0, 1, vertexBuffers, offsets);

    vkCmdBindIndexBuffer(entry.commandBuffer, entry.pIndexBuffer->getIndexBuffer(), 0, VK_INDEX_TYPE_UINT16);

    vkCmdDrawIndexed(entry.commandBuffer, static_cast<uint32_t>(entry.pIndexBuffer->getIndexSize()), 1, 0, 0, 0);
    vkCmdEndRenderPass(entry.commandBuffer);
    if (vkEndCommandBuffer(entry.commandBuffer) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to record command buffer!");
    }
}