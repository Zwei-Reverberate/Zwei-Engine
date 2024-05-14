#include <include/vulkan/zwrenderutils.h>
#include <include/renderdata/zwvertex.h>

VkVertexInputBindingDescription ZwRenderUtils::getBindingDescription()
{
    VkVertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0; // 现在的顶点数据都打包在一个数组中，因此只有一个绑定
    bindingDescription.stride = sizeof(ZwVertex); // 指定从一个条目到下一个条目的字节数
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX; // 暂未使用实例化渲染
    return bindingDescription;
}

std::array<VkVertexInputAttributeDescription, 2> ZwRenderUtils::getAttributeDescriptions()
{
    std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
    attributeDescriptions[0].binding = 0; // 告诉 Vulkan 每个顶点数据来自哪个绑定
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions[0].offset = ZwVertex::getPosOffset();

    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[1].offset = ZwVertex::getColorOffset();

    return attributeDescriptions;
}