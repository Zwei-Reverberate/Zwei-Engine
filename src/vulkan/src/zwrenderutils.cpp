#include <include/vulkan/zwrenderutils.h>
#include <include/renderdata/zwvertex.h>

VkVertexInputBindingDescription ZwRenderUtils::getBindingDescription()
{
    VkVertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0; // ���ڵĶ������ݶ������һ�������У����ֻ��һ����
    bindingDescription.stride = sizeof(ZwVertex); // ָ����һ����Ŀ����һ����Ŀ���ֽ���
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX; // ��δʹ��ʵ������Ⱦ
    return bindingDescription;
}

std::array<VkVertexInputAttributeDescription, 2> ZwRenderUtils::getAttributeDescriptions()
{
    std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
    attributeDescriptions[0].binding = 0; // ���� Vulkan ÿ���������������ĸ���
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions[0].offset = ZwVertex::getPosOffset();

    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[1].offset = ZwVertex::getColorOffset();

    return attributeDescriptions;
}