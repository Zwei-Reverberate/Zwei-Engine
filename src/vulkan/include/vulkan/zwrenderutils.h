#ifndef ZWRENDERUTILS_H
#define ZWRENDERUTILS_H
#include <array>
#include <vector>
#include <include/vulkan/zwlogicaldevice.h>
#include <include/vulkan/zwvulkanoption.h>

class ZwRenderUtils
{
public:
	static VkVertexInputBindingDescription getBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions(); // 现在只有位置和颜色两个属性
	
	static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, ZwPhysicalDevice* pPhysicalDevice);
	static CreateBufferResult createBuffer(const CreateBufferEntry& entry);
	static void copyBuffer(const CopyBufferEntry& entry);

	static void recordCommandBuffer(const RecordCommandBufferEntry& entry);

	static void updateUniformBuffer(const UpdateUniformBufferEntry& entry);

	static CreateImageResult createImage(const CreateImageEntry& entry);

	static VkCommandBuffer beginSingleTimeCommands(ZwLogicalDevice* pLogicalDevice, ZwCommandManager* pCommandManager);
	static void endSingleTimeCommands(VkCommandBuffer commandBuffer, ZwLogicalDevice* pLogicalDevice, ZwCommandManager* pCommandManager);

	static void transitionImageLayout(const TransitionImageLayoutEntry& entry);

	static void copyBufferToImage(const CopyBufferToImageEntry& entry);

	static VkImageView createImageView(const CreateImageViewEntry& entry);

	static VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features, VkPhysicalDevice physicalDevice);
	static VkFormat findDepthFormat(VkPhysicalDevice physicalDevice);
	static bool hasStencilComponent(VkFormat format);
};

#endif // !ZWRENDERUTILS_H
