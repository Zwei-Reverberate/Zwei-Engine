#ifndef ZWDESCRIPTOR_H
#define ZWDESCRIPTOR_H
#include <include/vulkan/zwlogicaldevice.h>
#include <include/renderobject/zwtoolid.h>
#include <vector>
#include <map>

class ZwUniformBuffers;
class ZwTextureManager;
class ZwDescriptor
{
public:
	void init(ZwLogicalDevice* pLogicalDevice,  ZwUniformBuffers* pUniformBuffers, ZwTextureManager* pTextureManager);
	void destroy(ZwLogicalDevice* pLogicalDevice);

	const VkDescriptorSet& getDescriptorSet(int curFrame, ZwToolId id) const { return m_descriptorSets[curFrame].find(id)->second; }
	const VkDescriptorSetLayout& getDescriptorSetLayout() const { return m_descriptorSetLayout; }

private:
	void initLayout(ZwLogicalDevice* pLogicalDevice);
	void initPool(ZwLogicalDevice* pLogicalDevice, int size);


private:
	VkDescriptorSetLayout m_descriptorSetLayout;
	VkDescriptorPool m_descriptorPool;
	std::vector<std::map<ZwToolId, VkDescriptorSet>> m_descriptorSets;
};

#endif // !ZWDESCRIPTOR_H
