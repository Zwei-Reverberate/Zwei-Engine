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
	VkSemaphore m_imageAvailableSemaphore; // ��ʶ��׼������Ⱦ
	VkSemaphore m_renderFinishedSemaphore; // ��ʶ��Ⱦ�����
	VkFence m_inFlightFence; // ȷ��ÿ��ֻ��Ⱦһ֡
};

#endif