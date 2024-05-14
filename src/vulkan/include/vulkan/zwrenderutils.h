#ifndef ZWRENDERUTILS_H
#define ZWRENDERUTILS_H
#include <array>
#include <include/vulkan/zwlogicaldevice.h>

class ZwRenderUtils
{
public:
	static VkVertexInputBindingDescription getBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions(); // 现在只有位置和颜色两个属性
};

#endif // !ZWRENDERUTILS_H
