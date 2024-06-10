#include <include/vulkan/zwcommandmanager.h>
#include <include/vulkan/zwphysicaldevice.h>
#include <include/vulkan/zwsurface.h>
#include <include/vulkan/zwqueuefamilyindices.h>
#include <include/vulkan/vulkanconst.h>
#include <stdexcept>

void ZwCommandManager::init(ZwPhysicalDevice* pPhysicalDevice, ZwLogicalDevice* pLogicalDevice, ZwSurface* pSurface)
{
	if (!pPhysicalDevice || !pLogicalDevice || !pSurface)
		return;

	ZwQueueFamilyIndices queueFamilyIndices = ZwQueueFamilyIndices::findQueueFamilies(pPhysicalDevice->getDevice(), pSurface->getSurface());

	// command pool
	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = queueFamilyIndices.m_graphicsFamily.value();
	if (vkCreateCommandPool(pLogicalDevice->getDevice(), &poolInfo, nullptr, &m_commandPool) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create command pool!");
	}


	// command buffers
	m_commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = m_commandPool; // 指定 commandPool
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY; // 指定是主 command buffer 还是辅助 command buffer，此处是主 command buffer
	allocInfo.commandBufferCount = (uint32_t)m_commandBuffers.size();; // 指定分配的数量

	if (vkAllocateCommandBuffers(pLogicalDevice->getDevice(), &allocInfo, m_commandBuffers.data()) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate command buffers!");
	}
}


void ZwCommandManager::destroy(ZwLogicalDevice* pLogicalDevice)
{
	if (!pLogicalDevice)
		return;
	vkDestroyCommandPool(pLogicalDevice->getDevice(), m_commandPool, nullptr);
}