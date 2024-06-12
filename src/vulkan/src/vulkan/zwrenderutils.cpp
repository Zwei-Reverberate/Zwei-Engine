#include <include/vulkan/zwrenderutils.h>
#include <include/renderdata/zwvertex.h>
#include <include/vulkan/zwcommandmanager.h>
#include <include/vulkan/zwframebuffers.h>
#include <include/vulkan/zwrenderpass.h>
#include <include/vulkan/zwgraphicpipeline.h>
#include <include/vulkan/zwswapchain.h>
#include <include/renderobject/zwrenderobjectmanager.h>
#include <include/vulkan/zwuniformbuffers.h>
#include <include/renderdata/zwuniform.h>
#include <include/vulkan/zwdescriptor.h>
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept>
#include <chrono>

VkVertexInputBindingDescription ZwRenderUtils::getBindingDescription()
{
    VkVertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0; // 现在的顶点数据都打包在一个数组中，因此只有一个绑定
    bindingDescription.stride = sizeof(ZwVertex); // 指定从一个条目到下一个条目的字节数
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX; // 暂未使用实例化渲染
    return bindingDescription;
}

std::array<VkVertexInputAttributeDescription, 3> ZwRenderUtils::getAttributeDescriptions()
{
    std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};
    attributeDescriptions[0].binding = 0; // 告诉 Vulkan 每个顶点数据来自哪个绑定
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[0].offset = ZwVertex::getPosOffset();
        
    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[1].offset = ZwVertex::getColorOffset();

    attributeDescriptions[2].binding = 0;
    attributeDescriptions[2].location = 2;
    attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions[2].offset = ZwVertex::getTexCoordOffset();

    return attributeDescriptions;
}


uint32_t ZwRenderUtils::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, ZwPhysicalDevice* pPhysicalDevice)
{
    if (!pPhysicalDevice)
        return uint32_t();
    VkPhysicalDeviceMemoryProperties memProperties; // 查询可用的内存类型信息
    vkGetPhysicalDeviceMemoryProperties(pPhysicalDevice->getDevice(), &memProperties);
    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
            return i;
    }
    throw std::runtime_error("failed to find suitable memory type!");
}


CreateBufferResult ZwRenderUtils::createBuffer(const CreateBufferEntry& entry)
{
    CreateBufferResult result{};

    if (!entry.pLogicalDevice || !entry.pPhysicalDevice)
        return result;

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = entry.size;
    bufferInfo.usage = entry.usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(entry.pLogicalDevice->getDevice(), &bufferInfo, nullptr, &result.buffer) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(entry.pLogicalDevice->getDevice(), result.buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, entry.properties, entry.pPhysicalDevice);

    if (vkAllocateMemory(entry.pLogicalDevice->getDevice(), &allocInfo, nullptr, &result.bufferMemory) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    vkBindBufferMemory(entry.pLogicalDevice->getDevice(), result.buffer, result.bufferMemory, 0);

    result.sucess = true;
    return result;
}


void ZwRenderUtils::copyBuffer(const CopyBufferEntry& entry)
{
    if (!entry.pLogicalDevice || !entry.pCommandManager)
        return;

    VkCommandBuffer commandBuffer = ZwRenderUtils::beginSingleTimeCommands(entry.pLogicalDevice, entry.pCommandManager);

    VkBufferCopy copyRegion{};
    copyRegion.size = entry.size;
    vkCmdCopyBuffer(commandBuffer, entry.srcBuffer, entry.dstBuffer, 1, &copyRegion);

    ZwRenderUtils::endSingleTimeCommands(commandBuffer, entry.pLogicalDevice, entry.pCommandManager);
}


void ZwRenderUtils::recordCommandBuffer(const RecordCommandBufferEntry& entry)
{
    if (!entry.pFramebuffers || !entry.pGraphicsPipeline || !entry.pObjectManager || !entry.pRenderPass || !entry.pSwapChain || !entry.pDescriptor)
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

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = { {0.0f, 0.0f, 0.0f, 1.0f} };
    clearValues[1].depthStencil = { 1.0f, 0 };

    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(entry.commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

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


    /*
        每帧重新绑定操作虽然不会导致数据重新传输，但仍会带来一定的性能开销
        为了优化性能，可以考虑预先记录命令缓冲区并在每帧中复用它们，同时仅在必要时重新绑定资源和状态
     */
    const std::vector<std::unique_ptr<ZwRenderObject>>& renderObjects = entry.pObjectManager->getRenderObjects();
    for (int i = 0; i < renderObjects.size(); ++i)
    {
        const std::unique_ptr<ZwRenderObject>& pObject = renderObjects[i];
        if (!pObject)
            continue;

        vkCmdBindPipeline(entry.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, entry.pGraphicsPipeline->getGraphicsPipeline(pObject->getPipeLineId())); //  temp
       
        VkBuffer vertexBuffers[] = { pObject->getVertexBuffer()};
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(entry.commandBuffer, 0, 1, vertexBuffers, offsets);

        vkCmdBindIndexBuffer(entry.commandBuffer, pObject->getIndexBuffer(), 0, VK_INDEX_TYPE_UINT32);

        vkCmdBindDescriptorSets(entry.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, entry.pGraphicsPipeline->getPipelineLayout(), 0, 1, &entry.pDescriptor->getDescriptorSet(entry.currentFrame, pObject->getDescriptorSetsId()), 0, nullptr); // temp
        vkCmdDrawIndexed(entry.commandBuffer, static_cast<uint32_t>(pObject->getIndexSize()), 1, 0, 0, 0);
    }

    vkCmdEndRenderPass(entry.commandBuffer);
    if (vkEndCommandBuffer(entry.commandBuffer) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to record command buffer!");
    }
}


void ZwRenderUtils::updateUniformBuffer(const UpdateUniformBufferEntry& entry)
{
    if (!entry.pSwapChain || !entry.pUniformBuffers)
        return;

    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    ZwUniform ubo{};
    ubo.setModelMat(glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    ubo.setViewMat(glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), entry.pSwapChain->getSwapChainExtent().width / (float)entry.pSwapChain->getSwapChainExtent().height, 0.1f, 10.0f);
    proj[1][1] *= -1;
    ubo.setProjMat(proj);
    memcpy(entry.pUniformBuffers->getUniformBuffersMapped()[entry.currentImage], &ubo, sizeof(ubo));
}


CreateImageResult ZwRenderUtils::createImage(const CreateImageEntry& entry)
{
    CreateImageResult result{};
    if (!entry.pLogicalDevice)
        return result;
        
    VkImageCreateInfo imageInfo{};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.extent.width = entry.width;
    imageInfo.extent.height = entry.height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = entry.format;
    imageInfo.tiling = entry.tiling;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageInfo.usage = entry.usage;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    VkImage image;
    VkDeviceMemory imageMemory;
    if (vkCreateImage(entry.pLogicalDevice->getDevice(), &imageInfo, nullptr, &image) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create image!");
    }
    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(entry.pLogicalDevice->getDevice(), image, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = ZwRenderUtils::findMemoryType(memRequirements.memoryTypeBits, entry.properties, entry.pPhysicalDevice);
    if (vkAllocateMemory(entry.pLogicalDevice->getDevice(), &allocInfo, nullptr, &imageMemory) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to allocate image memory!");
    }
    vkBindImageMemory(entry.pLogicalDevice->getDevice(), image, imageMemory, 0);

    result.image = image;
    result.imageMemory = imageMemory;
    result.sucess = true;

    return result;
}


VkCommandBuffer ZwRenderUtils::beginSingleTimeCommands(ZwLogicalDevice* pLogicalDevice, ZwCommandManager* pCommandManager)
{
    VkCommandBuffer commandBuffer{};
    if (!pCommandManager || !pLogicalDevice)
        return commandBuffer;

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = pCommandManager->getCommandPool();
    allocInfo.commandBufferCount = 1;

    vkAllocateCommandBuffers(pLogicalDevice->getDevice(), &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
}

void ZwRenderUtils::endSingleTimeCommands(VkCommandBuffer commandBuffer, ZwLogicalDevice* pLogicalDevice, ZwCommandManager* pCommandManager)
{
    if (!pLogicalDevice || !pCommandManager)
        return;

    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(pLogicalDevice->getGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(pLogicalDevice->getGraphicsQueue());

    vkFreeCommandBuffers(pLogicalDevice->getDevice(), pCommandManager->getCommandPool(), 1, &commandBuffer);
}


void ZwRenderUtils::transitionImageLayout(const TransitionImageLayoutEntry& entry)
{
    if (!entry.pCommandManager || !entry.pLogicalDevice)
        return;

    VkCommandBuffer commandBuffer = beginSingleTimeCommands(entry.pLogicalDevice, entry.pCommandManager);

    VkImageMemoryBarrier barrier{};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout = entry.oldLayout;
    barrier.newLayout = entry.newLayout;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = entry.image;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;

    VkPipelineStageFlags sourceStage;
    VkPipelineStageFlags destinationStage;

    if (entry.oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && entry.newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) 
    {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (entry.oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && entry.newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) 
    {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else 
    {
        throw std::invalid_argument("unsupported layout transition!");
    }

    vkCmdPipelineBarrier
    (
        commandBuffer,
        sourceStage, destinationStage,
        0,
        0, nullptr,
        0, nullptr,
        1, &barrier
    );

    endSingleTimeCommands(commandBuffer, entry.pLogicalDevice, entry.pCommandManager);
}


void ZwRenderUtils::copyBufferToImage(const CopyBufferToImageEntry& entry)
{
    if (!entry.pLogicalDevice || !entry.pCommandManager)
        return;

    VkCommandBuffer commandBuffer = ZwRenderUtils::beginSingleTimeCommands(entry.pLogicalDevice, entry.pCommandManager);

    VkBufferImageCopy region{};
    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;
    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;
    region.imageOffset = { 0, 0, 0 };
    region.imageExtent = 
    {
        entry.width,
        entry.height,
        1
    };

    vkCmdCopyBufferToImage(commandBuffer, entry.buffer, entry.image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

    ZwRenderUtils::endSingleTimeCommands(commandBuffer, entry.pLogicalDevice, entry.pCommandManager);
}



VkImageView ZwRenderUtils::createImageView(const CreateImageViewEntry& entry)
{
    VkImageView imageView = nullptr;
    if (!entry.pLogicalDevice)
        return imageView;

    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = entry.image;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = entry.format;
    viewInfo.subresourceRange.aspectMask = entry.aspectFlags;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    if (vkCreateImageView(entry.pLogicalDevice->getDevice(), &viewInfo, nullptr, &imageView) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create texture image view!");
    }
    return imageView;
}

VkFormat ZwRenderUtils::findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features, VkPhysicalDevice physicalDevice)
{
    for (VkFormat format : candidates)
    {
        VkFormatProperties props;
        vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

        if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) 
        {
            return format;
        }
        else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) 
        {
            return format;
        }
    }

    throw std::runtime_error("failed to find supported format!");
}


VkFormat ZwRenderUtils::findDepthFormat(VkPhysicalDevice physicalDevice)
{
    return ZwRenderUtils::findSupportedFormat
    (
        { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
        VK_IMAGE_TILING_OPTIMAL,
        VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT, 
        physicalDevice
    );
}           
        
bool ZwRenderUtils::hasStencilComponent(VkFormat format)
{
    return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
}