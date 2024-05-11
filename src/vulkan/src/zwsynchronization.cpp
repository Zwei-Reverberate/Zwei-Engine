#include <include/vulkan/zwsynchronization.h>
#include <include/vulkan/vulkanconst.h>
#include <stdexcept>

void ZwSynchronization::init(ZwLogicalDevice* pLogicalDevice)
{
	if (!pLogicalDevice)
		return;

    m_imageAvailableSemaphore.resize(MAX_FRAMES_IN_FLIGHT);
    m_renderFinishedSemaphore.resize(MAX_FRAMES_IN_FLIGHT);
    m_inFlightFence.resize(MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        if (vkCreateSemaphore(pLogicalDevice->getDeviceConst(), &semaphoreInfo, nullptr, &m_imageAvailableSemaphore[i]) != VK_SUCCESS ||
            vkCreateSemaphore(pLogicalDevice->getDeviceConst(), &semaphoreInfo, nullptr, &m_renderFinishedSemaphore[i]) != VK_SUCCESS ||
            vkCreateFence(pLogicalDevice->getDeviceConst(), &fenceInfo, nullptr, &m_inFlightFence[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
    }
}


void ZwSynchronization::destroy(ZwLogicalDevice* pLogicalDevice)
{
	if (!pLogicalDevice)
		return;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        vkDestroySemaphore(pLogicalDevice->getDeviceConst(), m_renderFinishedSemaphore[i], nullptr);
        vkDestroySemaphore(pLogicalDevice->getDeviceConst(), m_imageAvailableSemaphore[i], nullptr);
        vkDestroyFence(pLogicalDevice->getDeviceConst(), m_inFlightFence[i], nullptr);
    }
}