#ifndef ZWSYNCHRONIZATION_H
#define ZWSYNCHRONIZATION_H
#include <include/vulkan/zwlogicaldevice.h>

class ZwSynchronization
{
public:
	void init(ZwLogicalDevice* pLogicalDevice);
	void destroy(ZwLogicalDevice* pLogicalDevice);
	
	const VkSemaphore& getImageAvailableSemaphore() const {return m_imageAvailableSemaphore;}
	const VkSemaphore& getRenderFinishedSemaphore() const { return m_renderFinishedSemaphore; }
	const VkFence& getInFlightFence() const { return m_inFlightFence; }

private:
	VkSemaphore m_imageAvailableSemaphore; // 标识已准备好渲染
	VkSemaphore m_renderFinishedSemaphore; // 标识渲染已完成
	VkFence m_inFlightFence; // 确保每次只渲染一帧
};

#endif