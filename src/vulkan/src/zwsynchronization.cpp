#include <include/vulkan/zwsynchronization.h>
#include <stdexcept>

void ZwSynchronization::init(ZwLogicalDevice* pLogicalDevice)
{
	if (!pLogicalDevice)
		return;
    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    if (vkCreateSemaphore(pLogicalDevice->getDeviceConst(), &semaphoreInfo, nullptr, &m_imageAvailableSemaphore) != VK_SUCCESS ||
        vkCreateSemaphore(pLogicalDevice->getDeviceConst(), &semaphoreInfo, nullptr, &m_renderFinishedSemaphore) != VK_SUCCESS ||
        vkCreateFence(pLogicalDevice->getDeviceConst(), &fenceInfo, nullptr, &m_inFlightFence) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create synchronization objects for a frame!");
    }
}


void ZwSynchronization::destroy(ZwLogicalDevice* pLogicalDevice)
{
	if (!pLogicalDevice)
		return;

    vkDestroySemaphore(pLogicalDevice->getDeviceConst(), m_renderFinishedSemaphore, nullptr);
    vkDestroySemaphore(pLogicalDevice->getDeviceConst(), m_imageAvailableSemaphore, nullptr);
    vkDestroyFence(pLogicalDevice->getDeviceConst(), m_inFlightFence, nullptr);
}