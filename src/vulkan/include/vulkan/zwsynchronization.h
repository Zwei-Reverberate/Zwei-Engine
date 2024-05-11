#ifndef ZWSYNCHRONIZATION_H
#define ZWSYNCHRONIZATION_H
#include <include/vulkan/zwlogicaldevice.h>
#include <vector>

class ZwSynchronization
{
public:
	void init(ZwLogicalDevice* pLogicalDevice);
	void destroy(ZwLogicalDevice* pLogicalDevice);
	
	const std::vector<VkSemaphore>& getImageAvailableSemaphore() const {return m_imageAvailableSemaphore;}
	const std::vector<VkSemaphore>& getRenderFinishedSemaphore() const { return m_renderFinishedSemaphore; }
	const std::vector<VkFence>& getInFlightFence() const { return m_inFlightFence; }

private:
	std::vector<VkSemaphore> m_imageAvailableSemaphore; // 标识已准备好渲染
	std::vector<VkSemaphore> m_renderFinishedSemaphore; // 标识渲染已完成
	std::vector<VkFence> m_inFlightFence; // 确保每次只渲染一帧
};

#endif