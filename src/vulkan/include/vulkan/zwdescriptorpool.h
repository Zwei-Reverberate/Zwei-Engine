#ifndef ZWDESCRIPTORPOOL_H
#define ZWDESCRIPTORPOOL_H
#include <include/vulkan/zwlogicaldevice.h>

class ZwDescriptorPool
{
public:
	void init(ZwLogicalDevice* pLogicalDevice);
	void destroy(ZwLogicalDevice* pLogicalDevice);

	const VkDescriptorPool& getDescriptorPool() const { return m_descriptorPool; }

private:
	VkDescriptorPool m_descriptorPool;
};

#endif // !ZWDESCRIPTORPOOL_H
