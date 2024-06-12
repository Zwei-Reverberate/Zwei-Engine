#include <include/vulkan/zwuniformbuffers.h>
#include <include/vulkan/vulkanconst.h>
#include <include/vulkan/zwrenderutils.h>
#include <include/renderdata/zwuniform.h>


void ZwUniformBuffers::init(ZwLogicalDevice* pLogicalDevice, ZwPhysicalDevice* pPhysicalDevice)
{
	if (!pLogicalDevice || !pPhysicalDevice)
		return;

	VkDeviceSize bufferSize = sizeof(ZwUniform);

	m_uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
	m_uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
	m_uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		CreateBufferEntry createEntry;
		createEntry.size = bufferSize;
		createEntry.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
		createEntry.properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
		createEntry.pLogicalDevice = pLogicalDevice;
		createEntry.pPhysicalDevice = pPhysicalDevice;

		CreateBufferResult createRes = ZwRenderUtils::createBuffer(createEntry);
		if (!createRes.sucess)
			return;
		m_uniformBuffers[i] = createRes.buffer;
		m_uniformBuffersMemory[i] = createRes.bufferMemory;

		vkMapMemory(pLogicalDevice->getDevice(), m_uniformBuffersMemory[i], 0, bufferSize, 0, &m_uniformBuffersMapped[i]);
	}
}


void ZwUniformBuffers::destroy(ZwLogicalDevice* pLogicalDevice)
{
	if (!pLogicalDevice)
		return;
	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) 
	{
		vkDestroyBuffer(pLogicalDevice->getDevice(), m_uniformBuffers[i], nullptr);
		vkFreeMemory(pLogicalDevice->getDevice(), m_uniformBuffersMemory[i], nullptr);
	}
}