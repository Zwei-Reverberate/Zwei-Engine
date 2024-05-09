#include <include/vulkan/zwrenderpass.h>
#include <include/vulkan/zwswapchain.h>
#include <stdexcept>

void ZwRenderPass::init(ZwLogicalDevice* pLogicalDevice, ZwSwapChain* pSwapChain)
{
	if (!pLogicalDevice || !pSwapChain)
		return;

	VkAttachmentDescription colorAttachment{};
	// color attachment �� formant Ӧ�ú� swap chain �� image format ��ƥ��
	colorAttachment.format = pSwapChain->getSwapChainImageFormat();
	// �趨����������Ϊû��ʹ�ö��ز�������������Ϊ 1
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef{};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass{};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	VkRenderPassCreateInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	if (vkCreateRenderPass(pLogicalDevice->getDeviceConst(), &renderPassInfo, nullptr, &m_renderPass) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create render pass!");
	}
}

void ZwRenderPass::destroy(ZwLogicalDevice* pLogicalDevice)
{
	if (!pLogicalDevice)
		return;
	vkDestroyRenderPass(pLogicalDevice->getDeviceConst(), m_renderPass, nullptr);
}
