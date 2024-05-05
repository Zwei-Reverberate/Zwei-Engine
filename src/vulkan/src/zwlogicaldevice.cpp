#include <include/vulkan/zwlogicaldevice.h>
#include <include/vulkan/zwqueuefamilyindices.h>
#include <include/vulkan/vulkanconst.h>
#include <include/vulkan/zwsurface.h>
#include <stdexcept>
#include <set>

void ZwLogicalDevice::init(const ZwPhysicalDevice* pPhysicalDevice, const ZwSurface* pSurface)
{
	if (!pPhysicalDevice || !pSurface)
		return;
	ZwQueueFamilyIndices indices = ZwQueueFamilyIndices::findQueueFamilies(pPhysicalDevice->getDeviceConst(), pSurface->getSurfaceConst());

	VkDeviceQueueCreateInfo queueCreateInfo{}; // VkDeviceQueueCreateInfo 描述了单个 queue family 所需要的队列数
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = indices.m_graphicsFamily.value();
	queueCreateInfo.queueCount = 1;

	// 使用一个 set 创建来自两个 queue family 的 queue
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueueFamilies = { indices.m_graphicsFamily.value(), indices.m_presentFamily.value() };
	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueCreateInfo{};
		// VkDeviceQueueCreateInfo 描述了单个 queue family 所需要的队列数
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkPhysicalDeviceFeatures deviceFeatures{};
	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;
	createInfo.pEnabledFeatures = &deviceFeatures;
	// 启用 swap chain 需要 VK_KHR_swapchain 先启用扩展
	createInfo.enabledExtensionCount = static_cast<uint32_t>(DEVICE_EXTENSIONS.size());
	createInfo.ppEnabledExtensionNames = DEVICE_EXTENSIONS.data();
	if (ENABLEVALIDATIONLAYERS)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(VALIDATION_LAYERS.size());
		createInfo.ppEnabledLayerNames = VALIDATION_LAYERS.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(pPhysicalDevice->getDeviceConst(), &createInfo, nullptr, &m_device) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create logical device!");
	}
	vkGetDeviceQueue(m_device, indices.m_graphicsFamily.value(), 0, &m_graphicsQueue);
}

void ZwLogicalDevice::destroy()
{
	vkDestroyDevice(m_device, nullptr);
}