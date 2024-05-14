#include <include/vulkan/zwvertexbuffer.h>
#include <stdexcept>
#include <include/renderdata/zwvertex.h>

void ZwVertexBuffer ::init(ZwLogicalDevice* pLogicalDevice, ZwPhysicalDevice* pPhysicalDevice, const std::vector<ZwVertex>& zwVertices)
{
	if (!pLogicalDevice || !pPhysicalDevice || zwVertices.empty())
		return;

	m_vertexSize = zwVertices.size();

    // 创建 vertex buffer
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = sizeof(zwVertices[0]) * zwVertices.size();
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    if (vkCreateBuffer(pLogicalDevice->getDeviceConst(), &bufferInfo, nullptr, &m_vertexBuffer) != VK_SUCCESS)
        throw std::runtime_error("failed to create vertex buffer!");

    // 申请内存
    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(pLogicalDevice->getDeviceConst(), m_vertexBuffer, &memRequirements);

    // 分配内存
    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, pPhysicalDevice);
    if (vkAllocateMemory(pLogicalDevice->getDeviceConst(), &allocInfo, nullptr, &m_vertexBufferMemory) != VK_SUCCESS)
        throw std::runtime_error("failed to allocate vertex buffer memory!");

    // 关联内存与 vetex buffer
    vkBindBufferMemory(pLogicalDevice->getDeviceConst(), m_vertexBuffer, m_vertexBufferMemory, 0);

    // 将顶点数据复制到 buffer 中
    void* data;
    vkMapMemory(pLogicalDevice->getDeviceConst(), m_vertexBufferMemory, 0, bufferInfo.size, 0, &data);
    std::memcpy(data, zwVertices.data(), (size_t)bufferInfo.size);
    vkUnmapMemory(pLogicalDevice->getDeviceConst(), m_vertexBufferMemory);
}

void ZwVertexBuffer ::destroy(ZwLogicalDevice* pLogicalDevice)
{
    if (!pLogicalDevice)
        return;
    vkDestroyBuffer(pLogicalDevice->getDeviceConst(), m_vertexBuffer, nullptr);
    vkFreeMemory(pLogicalDevice->getDeviceConst(), m_vertexBufferMemory, nullptr);
}


uint32_t ZwVertexBuffer ::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, ZwPhysicalDevice* pPhysicalDevice)
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
