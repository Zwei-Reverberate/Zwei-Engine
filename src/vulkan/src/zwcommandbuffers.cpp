#include <include/vulkan/zwcommandbuffers.h>
#include <include/vulkan/zwcommandpool.h>
#include <include/vulkan/vulkanconst.h>
#include <stdexcept>

void ZwCommandBuffers::init(ZwLogicalDevice* pLogicalDevice, ZwCommandPool* pCommandPool)
{
	if (!pLogicalDevice || !pCommandPool)
		return;

    m_commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = pCommandPool->getCommandPool(); // ָ�� commandPool
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY; // ָ������ command buffer ���Ǹ��� command buffer���˴����� command buffer
    allocInfo.commandBufferCount = (uint32_t)m_commandBuffers.size();; // ָ�����������

    if (vkAllocateCommandBuffers(pLogicalDevice->getDeviceConst(), &allocInfo, m_commandBuffers.data()) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}