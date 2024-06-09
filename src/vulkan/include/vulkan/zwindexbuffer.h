#ifndef ZWINDEXBUFFER_H
#define ZWINDEXBUFFER_H
#include <include/vulkan/zwlogicaldevice.h>
#include <vector>

class ZwCommandPool;
class ZwVertex;
class ZwIndexBuffer
{
public:
	void init(ZwLogicalDevice* pLogicalDevice, ZwPhysicalDevice* pPhysicalDevice, ZwCommandPool* pCommndPool, const std::vector<uint32_t>& zwIndices);
	void destroy(ZwLogicalDevice* pLogicalDevice);
	const VkBuffer& getIndexBuffer() const { return m_indexBuffer; }
	int getIndexSize() const { return m_indexSize; }

private:
	VkBuffer m_indexBuffer;
	VkDeviceMemory m_indexBufferMemory;
	int m_indexSize = 0;
};

#endif // !ZWINDEXBUFFER_H
