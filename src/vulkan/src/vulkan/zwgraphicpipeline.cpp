#include <include/vulkan/zwgraphicpipeline.h>
#include <include/vulkan/zwshader.h>
#include <include/vulkan/zwrenderpass.h>
#include <include/vulkan/zwrenderutils.h>
#include <include/vulkan/zwdescriptor.h>
#include <memory>
#include <vector>
#include <stdexcept>

void ZwGraphicPipeline::init(const std::vector<ShaderPath>& shaderPath, ZwLogicalDevice* pLogicalDevice, ZwRenderPass* pRenderPass, ZwDescriptor* pDescriptor)
{
	if (!pLogicalDevice || !pRenderPass || !pDescriptor)
		return;
	initLayout(pLogicalDevice, pDescriptor);
	
	for (int i = 0; i < shaderPath.size(); i++)
	{
		VkPipeline pipeLine = createPipeLine(shaderPath[i], pLogicalDevice, pRenderPass);
		if (pipeLine == VK_NULL_HANDLE)
			continue;
		m_pipelineMap.emplace(ZwToolId(i), pipeLine);
	}
}


void ZwGraphicPipeline::initLayout(ZwLogicalDevice* pLogicalDevice, ZwDescriptor* pDescriptor)
{
	if (!pLogicalDevice || !pDescriptor)
		return;
	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 1;
	pipelineLayoutInfo.pSetLayouts = &pDescriptor->getDescriptorSetLayout();
	if (vkCreatePipelineLayout(pLogicalDevice->getDevice(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create pipeline layout!");
	}
}

VkPipeline ZwGraphicPipeline::createPipeLine(const ShaderPath& shaderPath, ZwLogicalDevice* pLogicalDevice, ZwRenderPass* pRenderPass)
{
	if (!pLogicalDevice || !pRenderPass)
		return VK_NULL_HANDLE;
	VkPipeline graphicsPipeline = nullptr;
	
	// shader
	std::unique_ptr<ZwShader> pVertexShader = std::make_unique<ZwShader>();
	std::unique_ptr<ZwShader>  pFragmentShader = std::make_unique<ZwShader>();
	pVertexShader->init(shaderPath.vertexShaserPath, pLogicalDevice, ShaderType::VERTEX);
	pFragmentShader->init(shaderPath.fragmentShaderPath, pLogicalDevice, ShaderType::FRAGMENT);
	VkPipelineShaderStageCreateInfo shaderStages[] = { pVertexShader->getShaderStageInfo(), pFragmentShader->getShaderStageInfo() };

	// vertex input
	VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	auto bindingDescription = ZwRenderUtils::getBindingDescription();
	auto attributeDescriptions = ZwRenderUtils::getAttributeDescriptions();
	vertexInputInfo.vertexBindingDescriptionCount = 1;
	vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
	vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
	vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

	// Input assembly
	VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;

	// viewport state
	VkPipelineViewportStateCreateInfo viewportState{};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.scissorCount = 1;

	// rasterizer
	VkPipelineRasterizationStateCreateInfo rasterizer{};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_NONE;
	rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;

	// multisampling
	VkPipelineMultisampleStateCreateInfo multisampling{};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	VkPipelineDepthStencilStateCreateInfo depthStencil{};
	depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depthStencil.depthTestEnable = VK_TRUE;
	depthStencil.depthWriteEnable = VK_TRUE;
	depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
	depthStencil.depthBoundsTestEnable = VK_FALSE;
	depthStencil.stencilTestEnable = VK_FALSE;

	// color blending
	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;
	VkPipelineColorBlendStateCreateInfo colorBlending{};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY;
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;


	// dynamic state
	std::vector<VkDynamicState> dynamicStates =
	{
		   VK_DYNAMIC_STATE_VIEWPORT,
		   VK_DYNAMIC_STATE_SCISSOR
	};
	VkPipelineDynamicStateCreateInfo dynamicState{};
	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
	dynamicState.pDynamicStates = dynamicStates.data();

	// graphics pipeline
	VkGraphicsPipelineCreateInfo pipelineInfo{};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pDepthStencilState = &depthStencil;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.pDynamicState = &dynamicState;
	pipelineInfo.layout = m_pipelineLayout;
	pipelineInfo.renderPass = pRenderPass->getRenderPass();
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
	if (vkCreateGraphicsPipelines(pLogicalDevice->getDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create graphics pipeline!");
	}

	// shader destroy
	pVertexShader->destroy(pLogicalDevice);
	pFragmentShader->destroy(pLogicalDevice);

	return graphicsPipeline;
}

void ZwGraphicPipeline::destroy(ZwLogicalDevice* pLogicalDevice)
{
	if (!pLogicalDevice)
		return;
	for (auto& it : m_pipelineMap)
	{
		vkDestroyPipeline(pLogicalDevice->getDevice(), it.second, nullptr);
	}
	vkDestroyPipelineLayout(pLogicalDevice->getDevice(), m_pipelineLayout, nullptr);
}