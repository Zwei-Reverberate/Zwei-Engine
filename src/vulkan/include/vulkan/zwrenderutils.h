#ifndef ZWRENDERUTILS_H
#define ZWRENDERUTILS_H
#include <array>
#include <include/vulkan/zwlogicaldevice.h>
#include <include/vulkan/zwvulkanoption.h>

class ZwRenderUtils
{
public:
	static VkVertexInputBindingDescription getBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions(); // ����ֻ��λ�ú���ɫ��������
	
	static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, ZwPhysicalDevice* pPhysicalDevice);
	static CreateBufferResult createBuffer(const CreateBufferEntry& entry);
	static void copyBuffer(const CopyBufferEntry& entry);
};

#endif // !ZWRENDERUTILS_H
