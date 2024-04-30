#include <include/vulkan/zwlogicaldevice.h>
#include <include/vulkan/zwqueuefamilyindices.h>
#include <include/vulkan/vulkanconst.h>
#include <stdexcept>

void ZwLogicalDevice::init(const ZwPhysicalDevice* pPhysicalDevice)
{
	if (!pPhysicalDevice)
		return;
	ZwQueueFamilyIndices indices = ZwQueueFamilyIndices::findQueueFamilies(pPhysicalDevice->getDeviceConst());

	VkDeviceQueueCreateInfo queueCreateInfo{}; // VkDeviceQueueCreateInfo 描述了单个 queue family 所需要的队列数
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = indices.m_graphicsFamily.value();
	queueCreateInfo.queueCount = 1;

	// 为 Queue 分配优先级以影响命令缓冲区执行的调度
	float queuePriority = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	VkPhysicalDeviceFeatures deviceFeatures{};
	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = 0;
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