#ifndef ZWVULKANOPTION_H
#define ZWVULKANOPTION_H
#include <include/option/zwoption.h>
#include <include/vulkan/zwlogicaldevice.h>

class ZwCommandPool;
struct CreateBufferEntry : public ZwEntry
{
	VkDeviceSize size;
	VkBufferUsageFlags usage;
	VkMemoryPropertyFlags properties;

	ZwLogicalDevice* pLogicalDevice = nullptr;
	ZwPhysicalDevice* pPhysicalDevice = nullptr;
};

struct CreateBufferResult: public ZwResult
{
	VkBuffer buffer;
	VkDeviceMemory bufferMemory;
};

struct CopyBufferEntry : public ZwEntry
{
	VkBuffer srcBuffer; 
	VkBuffer dstBuffer;
	VkDeviceSize size;

	ZwLogicalDevice* pLogicalDevice = nullptr;
	ZwCommandPool* pCommandPool = nullptr;
};


#endif // !ZWVULKANOPTION_H
