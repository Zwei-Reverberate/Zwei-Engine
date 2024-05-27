#include <include/vulkan/zwvertexbuffer.h>
#include <stdexcept>
#include <include/renderdata/zwvertex.h>
#include <include/vulkan/zwrenderutils.h>
#include <include/vulkan/zwvulkanoption.h>

void ZwVertexBuffer ::init(ZwLogicalDevice* pLogicalDevice, ZwPhysicalDevice* pPhysicalDevice, ZwCommandPool* pCommndPool, const std::vector<ZwVertex>& zwVertices)
{
	if (!pLogicalDevice || !pPhysicalDevice || !pCommndPool || zwVertices.empty())
		return;

	m_vertexSize = zwVertices.size();

    VkDeviceSize bufferSize = sizeof(zwVertices[0]) * zwVertices.size();
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
    memcpy(data, zwVertices.data(), (size_t)bufferSize);
    vkUnmapMemory(pLogicalDevice->getDeviceConst(), stagingRes.bufferMemory);

    CreateBufferEntry vertexEntry;
    vertexEntry.pLogicalDevice = pLogicalDevice;
    vertexEntry.pPhysicalDevice = pPhysicalDevice;
    vertexEntry.size = bufferSize;
    vertexEntry.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    vertexEntry.properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    CreateBufferResult vertexRes = ZwRenderUtils::createBuffer(vertexEntry);
    if (!vertexRes.sucess)
        return;
    m_vertexBuffer = vertexRes.buffer;
    m_vertexBufferMemory = vertexRes.bufferMemory;
    
    CopyBufferEntry copyEntry;
    copyEntry.srcBuffer = stagingRes.buffer;
    copyEntry.dstBuffer = m_vertexBuffer;
    copyEntry.size = bufferSize;
    copyEntry.pLogicalDevice = pLogicalDevice;
    copyEntry.pCommandPool = pCommndPool;
    ZwRenderUtils::copyBuffer(copyEntry);

    vkDestroyBuffer(pLogicalDevice->getDeviceConst(), stagingRes.buffer, nullptr);
    vkFreeMemory(pLogicalDevice->getDeviceConst(), stagingRes.bufferMemory, nullptr);
}

void ZwVertexBuffer ::destroy(ZwLogicalDevice* pLogicalDevice)
{
    if (!pLogicalDevice)
        return;
    vkDestroyBuffer(pLogicalDevice->getDeviceConst(), m_vertexBuffer, nullptr);
    vkFreeMemory(pLogicalDevice->getDeviceConst(), m_vertexBufferMemory, nullptr);
}