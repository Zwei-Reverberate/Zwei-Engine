#ifndef ZWGRAPHICPIPELINE_H
#define ZWGRAPHICPIPELINE_H
#include <include/vulkan/zwlogicaldevice.h>
#include <include/converter/zwvulkantype.h>
#include <include/renderobject/zwtoolid.h>
#include <map>
#include <vector>

class ZwShader;
class ZwRenderPass;
class ZwVertexBuffer;
class ZwDescriptor;
class ZwGraphicPipeline
{
public:
	void init(const std::vector<ShaderPath>& shaderPath, ZwLogicalDevice* pLogicalDevice, ZwRenderPass* pRenderPass, ZwDescriptor* pDescriptor);
	void destroy(ZwLogicalDevice* pLogicalDevice);
	const VkPipeline& getGraphicsPipeline(const ZwToolId& id) const { return m_pipelineMap.find(id)->second; }
	const VkPipelineLayout& getPipelineLayout() const { return m_pipelineLayout; }

private:
	void initLayout(ZwLogicalDevice* pLogicalDevice, ZwDescriptor* pDescriptor);
	VkPipeline createPipeLine(const ShaderPath& shaderPath, ZwLogicalDevice* pLogicalDevice, ZwRenderPass* pRenderPass);

private:
	VkPipelineLayout m_pipelineLayout = nullptr;
	std::map<ZwToolId, VkPipeline> m_pipelineMap;
};

#endif

