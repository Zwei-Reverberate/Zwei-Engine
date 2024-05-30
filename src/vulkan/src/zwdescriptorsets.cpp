#include <include/vulkan/zwdescriptorsets.h>
#include <include/vulkan/zwdescriptorpool.h>
#include <include/vulkan/zwdescriptorsetlayout.h>
#include <include/vulkan/vulkanconst.h>
#include <include/vulkan/zwuniformbuffers.h>
#include <include/renderdata/zwuniform.h>
#include <stdexcept>


void ZwDescriptorSets::init(ZwLogicalDevice* pLogicalDevice, ZwDescriptorPool* pDescriptorPool, ZwDescriptorSetLayout* pDescriptorLayout, ZwUniformBuffers* pUniformBuffers)
{
	if (!pLogicalDevice || !pDescriptorPool || !pDescriptorLayout || !pUniformBuffers)
		return;

    std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, pDescriptorLayout->getDescriptorSetLayout());
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = pDescriptorPool->getDescriptorPool();
    allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
    allocInfo.pSetLayouts = layouts.data();

    m_descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
    if (vkAllocateDescriptorSets(pLogicalDevice->getDeviceConst(), &allocInfo, m_descriptorSets.data()) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }

    const std::vector<VkBuffer>& uniformBuffers = pUniformBuffers->getUniformBuffers();
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) 
    {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = uniformBuffers[i];
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(ZwUniform);

        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite.dstSet = m_descriptorSets[i];
        descriptorWrite.dstBinding = 0;
        descriptorWrite.dstArrayElement = 0;
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pBufferInfo = &bufferInfo;

        vkUpdateDescriptorSets(pLogicalDevice->getDeviceConst(), 1, &descriptorWrite, 0, nullptr);
    }
}
