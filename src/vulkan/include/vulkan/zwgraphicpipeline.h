#ifndef ZWGRAPHICPIPELINE_H
#define ZWGRAPHICPIPELINE_H
#include <include/vulkan/zwlogicaldevice.h>
#include <string>

class ZwShader;
class ZwRenderPass;
class ZwVertexBuffer;
class ZwDescriptorSetLayout;
class ZwGraphicPipeline
{
public:
	void init(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, ZwLogicalDevice* pLogicalDevice, ZwRenderPass* pRenderPass, ZwDescriptorSetLayout* pDescriptorSetLayout);
	void destroy(ZwLogicalDevice* pLogicalDevice);
	const VkPipeline& getGraphicsPipeline() const { return m_graphicsPipeline; }
	const VkPipelineLayout& getPipelineLayout() const { return m_pipelineLayout; }
private:
	VkPipelineLayout m_pipelineLayout = nullptr;
	VkPipeline m_graphicsPipeline = nullptr;
};

#endif

