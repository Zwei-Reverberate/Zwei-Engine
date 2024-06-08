#ifndef ZWVULKANOPTION_H
#define ZWVULKANOPTION_H
#include <include/option/zwoption.h>
#include <include/vulkan/zwlogicaldevice.h>

class ZwCommandPool;
class ZwFrameBuffers;
class ZwIndexBuffer;
class ZwRenderPass;
class ZwGraphicPipeline;
class ZwSwapChain;
class ZwVertexBuffer;
class ZwUniformBuffers;
class ZwDescriptorSets;
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

struct RecordCommandBufferEntry : public ZwEntry
{
	uint32_t imageIndex; 
	uint32_t currentFrame;
	VkCommandBuffer commandBuffer;
	
	ZwRenderPass* pRenderPass = nullptr;
	ZwFrameBuffers* pFramebuffers = nullptr;
	ZwGraphicPipeline* pGraphicsPipeline = nullptr;
	ZwSwapChain* pSwapChain = nullptr;
	ZwVertexBuffer* pVertexBuffer = nullptr;
	ZwIndexBuffer* pIndexBuffer = nullptr;
	ZwDescriptorSets* pDescriptorSets = nullptr;
};

struct UpdateUniformBufferEntry : public ZwEntry
{
	uint32_t currentImage;

	ZwSwapChain* pSwapChain = nullptr;
	ZwUniformBuffers* pUniformBuffers = nullptr;
};


struct CreateImageEntry : public ZwEntry
{
	uint32_t width;
	uint32_t height;
	VkFormat format;
	VkImageTiling tiling;
	VkImageUsageFlags usage;
	VkMemoryPropertyFlags properties;

	ZwLogicalDevice* pLogicalDevice = nullptr;
	ZwPhysicalDevice* pPhysicalDevice = nullptr;
};

struct CreateImageResult : public ZwResult
{
	VkImage image;
	VkDeviceMemory imageMemory;
};

struct TransitionImageLayoutEntry: public ZwEntry
{
	VkImage image;
	VkFormat format;
	VkImageLayout oldLayout;
	VkImageLayout newLayout;

	ZwLogicalDevice* pLogicalDevice = nullptr;
	ZwCommandPool* pCommandPool = nullptr;
};

struct CopyBufferToImageEntry : public ZwEntry
{
	VkBuffer buffer;
	VkImage image;
	uint32_t width;
	uint32_t height;

	ZwLogicalDevice* pLogicalDevice = nullptr;
	ZwCommandPool* pCommandPool = nullptr;
};

struct CreateImageViewEntry : public ZwEntry
{
	VkImage image;
	VkFormat format;
	VkImageAspectFlags aspectFlags;

	ZwLogicalDevice* pLogicalDevice = nullptr;
};


#endif // !ZWVULKANOPTION_H
