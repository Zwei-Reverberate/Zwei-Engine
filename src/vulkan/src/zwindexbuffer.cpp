#include <include/vulkan/zwindexbuffer.h>
#include <stdexcept>
#include <include/renderdata/zwvertex.h>
#include <include/vulkan/zwrenderutils.h>
#include <include/vulkan/zwvulkanoption.h>

void ZwIndexBuffer::init(ZwLogicalDevice* pLogicalDevice, ZwPhysicalDevice* pPhysicalDevice, ZwCommandPool* pCommndPool, const std::vector<uint32_t>& zwIndices)
{
    if (!pLogicalDevice || !pPhysicalDevice || !pCommndPool || zwIndices.empty())
        return;

    m_indexSize = zwIndices.size();

    VkDeviceSize bufferSize = sizeof(zwIndices[0]) * zwIndices.size();
    CreateBufferEntry stagingEntry;
    stagingEntry.pLogicalDevice = pLogicalDevice;
    stagingEntry.pPhysicalDevice = pPhysicalDevice;
    stagingEntry.size = bufferSize;
    stagingEntry.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    stagingEntry.properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
    CreateBufferResult stagingRes = ZwRenderUtils::createBuffer(stagingEntry);
    if (!stagingRes.sucess)
        return;

    void* data;
    vkMapMemory(pLogicalDevice->getDeviceConst(), stagingRes.bufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, zwIndices.data(), (size_t)bufferSize);
    vkUnmapMemory(pLogicalDevice->getDeviceConst(), stagingRes.bufferMemory);

    CreateBufferEntry indexEntry;
    indexEntry.pLogicalDevice = pLogicalDevice;
    indexEntry.pPhysicalDevice = pPhysicalDevice;
    indexEntry.size = bufferSize;
    indexEntry.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    indexEntry.properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    CreateBufferResult vertexRes = ZwRenderUtils::createBuffer(indexEntry);
    if (!vertexRes.sucess)
        return;
    m_indexBuffer = vertexRes.buffer;
    m_indexBufferMemory = vertexRes.bufferMemory;

    CopyBufferEntry copyEntry;
    copyEntry.srcBuffer = stagingRes.buffer;
    copyEntry.dstBuffer = m_indexBuffer;
    copyEntry.size = bufferSize;
    copyEntry.pLogicalDevice = pLogicalDevice;
    copyEntry.pCommandPool = pCommndPool;
    ZwRenderUtils::copyBuffer(copyEntry);

    vkDestroyBuffer(pLogicalDevice->getDeviceConst(), stagingRes.buffer, nullptr);
    vkFreeMemory(pLogicalDevice->getDeviceConst(), stagingRes.bufferMemory, nullptr);
}


void  ZwIndexBuffer::destroy(ZwLogicalDevice* pLogicalDevice)
{
    if (!pLogicalDevice)
        return;
    vkDestroyBuffer(pLogicalDevice->getDeviceConst(), m_indexBuffer, nullptr);
    vkFreeMemory(pLogicalDevice->getDeviceConst(), m_indexBufferMemory, nullptr);
}