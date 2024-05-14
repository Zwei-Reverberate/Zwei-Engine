#ifndef ZWRENDERUTILS_H
#define ZWRENDERUTILS_H
#include <array>
#include <include/vulkan/zwlogicaldevice.h>

class ZwRenderUtils
{
public:
	static VkVertexInputBindingDescription getBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions(); // ����ֻ��λ�ú���ɫ��������
};

#endif // !ZWRENDERUTILS_H
