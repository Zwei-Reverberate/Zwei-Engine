#ifndef ZWDESCRIPTORSETLAYOUT_H
#define ZWDESCRIPTORSETLAYOUT_H
#include <include/vulkan/zwlogicaldevice.h>

class ZwDescriptorSetLayout
{
public:
	void init(ZwLogicalDevice* pLogicalDevice);
	void destroy(ZwLogicalDevice* pLogicalDevice);

	const VkDescriptorSetLayout& getDescriptorSetLayout() const { return m_descriptorSetLayout; }

private:
	VkDescriptorSetLayout m_descriptorSetLayout;
};

#endif // !ZWDESCRIPTORSETLAYOUT_H
