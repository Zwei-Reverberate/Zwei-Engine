#ifndef ZWVERTEXBUFFER_H
#define ZWVERTEXBUFFER_H
#include <include/vulkan/zwlogicaldevice.h>
#include <vector>

class ZwVertex;
class ZwVertexBuffer 
{
public:
	void init(ZwLogicalDevice* pLogicalDevice, ZwPhysicalDevice* pPhysicalDevice, const std::vector<ZwVertex>& zwVertices);
	void destroy(ZwLogicalDevice* pLogicalDevice);
	static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, ZwPhysicalDevice* pPhysicalDevice);
	const VkBuffer& getVertexBuffer() const { return m_vertexBuffer; }
	int getVertexSize() const { return m_vertexSize; }

private:
	VkBuffer m_vertexBuffer;
	VkDeviceMemory m_vertexBufferMemory;
	int m_vertexSize = 0;
};

#endif // !ZWVERTEXBUFFR_H
