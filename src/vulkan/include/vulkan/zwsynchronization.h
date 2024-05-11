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
	std::vector<VkSemaphore> m_imageAvailableSemaphore; // ��ʶ��׼������Ⱦ
	std::vector<VkSemaphore> m_renderFinishedSemaphore; // ��ʶ��Ⱦ�����
	std::vector<VkFence> m_inFlightFence; // ȷ��ÿ��ֻ��Ⱦһ֡
};

#endif