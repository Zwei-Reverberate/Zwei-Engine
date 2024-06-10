#ifndef ZWDESCRIPTOR_H
#define ZWDESCRIPTOR_H
#include <include/vulkan/zwlogicaldevice.h>
#include <vector>

class ZwUniformBuffers;
class ZwTextureManager;
class ZwDescriptor
{
public:
	void init(ZwLogicalDevice* pLogicalDevice,  ZwUniformBuffers* pUniformBuffers, ZwTextureManager* pTextureManager);
	void destroy(ZwLogicalDevice* pLogicalDevice);

	const std::vector<VkDescriptorSet>& getDescriptorSet() const { return m_descriptorSets; }
	const VkDescriptorSetLayout& getDescriptorSetLayout() const { return m_descriptorSetLayout; }


private:
	VkDescriptorSetLayout m_descriptorSetLayout;
	VkDescriptorPool m_descriptorPool;
	std::vector<VkDescriptorSet> m_descriptorSets;
};

#endif // !ZWDESCRIPTOR_H
