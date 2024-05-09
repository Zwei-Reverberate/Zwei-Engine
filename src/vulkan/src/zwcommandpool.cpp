#include <include/vulkan/zwcommandpool.h>
#include <include/vulkan/zwphysicaldevice.h>
#include <include/vulkan/zwsurface.h>
#include <include/vulkan/zwqueuefamilyindices.h>
#include <stdexcept>

void ZwCommandPool::init(ZwPhysicalDevice* pPhysicalDevice, ZwLogicalDevice* pLogicalDevice, ZwSurface* pSurface)
{
	if (!pPhysicalDevice || !pLogicalDevice || !pSurface)
		return;

	ZwQueueFamilyIndices queueFamilyIndices = ZwQueueFamilyIndices::findQueueFamilies(pPhysicalDevice->getDeviceConst(), pSurface->getSurfaceConst()) ;

	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = queueFamilyIndices.m_graphicsFamily.value();
	if (vkCreateCommandPool(pLogicalDevice->getDeviceConst(), &poolInfo, nullptr, &m_commandPool) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create command pool!");
	}
}

void ZwCommandPool::destroy(ZwLogicalDevice* pLogicalDevice)
{
	if (!pLogicalDevice)
		return;
	vkDestroyCommandPool(pLogicalDevice->getDeviceConst(), m_commandPool, nullptr);
}