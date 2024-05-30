#ifndef ZWDESCRIPTORSETS_H
#define ZWDESCRIPTORSETS_H
#include <include/vulkan/zwlogicaldevice.h>
#include <vector>

class ZwDescriptorPool;
class ZwDescriptorSetLayout;
class ZwUniformBuffers;
class ZwDescriptorSets
{
public:
	void init(ZwLogicalDevice* pLogicalDevice, ZwDescriptorPool* pDescriptorPool, ZwDescriptorSetLayout* pDescriptorLayout, ZwUniformBuffers* pUniformBuffers);
	const std::vector<VkDescriptorSet>& getDescriptorSet() const { return m_descriptorSets; }

private:
	std::vector<VkDescriptorSet> m_descriptorSets;
};


#endif // !ZWDESCRIPTORSETS_H
