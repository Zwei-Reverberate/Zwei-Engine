#include <include/renderdata/zwtexture.h>
#include <include/vulkan/zwtexturemanager.h>
#include <include/vulkan/zwrenderutils.h>
#include <stdexcept>

void ZwTextureManager::init(std::vector<ZwTexture>& textures, ZwPhysicalDevice* pPhysicalDevice, ZwLogicalDevice* pLogicalDevice, ZwCommandPool* pCommandPool)
{
	if (textures.empty() || !pPhysicalDevice || !pLogicalDevice || !pCommandPool)
		return;

	m_images.resize(textures.size());
	m_textureImageMemories.resize(textures.size());
	m_textureImageViews.resize(textures.size());

	for (int i = 0; i < textures.size(); ++i)
	{
		VkDeviceSize imageSize =  textures[i].getTexWidth() * textures[i].getTexHeight() * 4;

		CreateBufferEntry createBufferEntry;
		createBufferEntry.size = imageSize;
		createBufferEntry.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
		createBufferEntry.properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
		createBufferEntry.pLogicalDevice = pLogicalDevice;
		createBufferEntry.pPhysicalDevice = pPhysicalDevice;

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		CreateBufferResult createBufferRes = ZwRenderUtils::createBuffer(createBufferEntry);
		if (!createBufferRes.sucess)
			continue;
		stagingBuffer = createBufferRes.buffer;
		stagingBufferMemory = createBufferRes.bufferMemory;

		void* data;
		vkMapMemory(pLogicalDevice->getDeviceConst(), stagingBufferMemory, 0, imageSize, 0, &data);
	    memcpy(data, textures[i].getPixels(), static_cast<size_t>(imageSize));
		vkUnmapMemory(pLogicalDevice->getDeviceConst(), stagingBufferMemory);
		textures[i].freePixels();

		CreateImageEntry createImageEntry;
		createImageEntry.width = textures[i].getTexWidth();
		createImageEntry.height = textures[i].getTexHeight();
		createImageEntry.format = VK_FORMAT_R8G8B8A8_SRGB;
		createImageEntry.tiling = VK_IMAGE_TILING_OPTIMAL;
		createImageEntry.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
		createImageEntry.properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
		createImageEntry.pLogicalDevice = pLogicalDevice;
		createImageEntry.pPhysicalDevice = pPhysicalDevice;

		CreateImageResult createImageRes = ZwRenderUtils::createImage(createImageEntry);
		if (!createImageRes.sucess)
			continue;

		m_images[i] = createImageRes.image;
		m_textureImageMemories[i] = createImageRes.imageMemory;


		TransitionImageLayoutEntry transEntry;
		transEntry.image = m_images[i];
		transEntry.format = VK_FORMAT_R8G8B8A8_SRGB;
		transEntry.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		transEntry.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		transEntry.pLogicalDevice = pLogicalDevice;
		transEntry.pCommandPool = pCommandPool;
		ZwRenderUtils::transitionImageLayout(transEntry);

		CopyBufferToImageEntry copyBufferToImageEntry;
		copyBufferToImageEntry.buffer = stagingBuffer;
		copyBufferToImageEntry.image = m_images[i];
		copyBufferToImageEntry.height = static_cast<uint32_t>(textures[i].getTexHeight());
		copyBufferToImageEntry.width = static_cast<uint32_t>(textures[i].getTexWidth());
		copyBufferToImageEntry.pLogicalDevice = pLogicalDevice;
		copyBufferToImageEntry.pCommandPool = pCommandPool;
		ZwRenderUtils::copyBufferToImage(copyBufferToImageEntry);

		transEntry.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		transEntry.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		ZwRenderUtils::transitionImageLayout(transEntry);

		vkDestroyBuffer(pLogicalDevice->getDeviceConst(), stagingBuffer, nullptr);
		vkFreeMemory(pLogicalDevice->getDeviceConst(), stagingBufferMemory, nullptr);


		CreateImageViewEntry createImageViewEntry;
		createImageViewEntry.format = VK_FORMAT_R8G8B8A8_SRGB;
		createImageViewEntry.image = m_images[i];
		createImageViewEntry.aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT;
		createImageViewEntry.pLogicalDevice = pLogicalDevice;
		VkImageView imageView = ZwRenderUtils::createImageView(createImageViewEntry);
		if (!imageView)
			return;
		m_textureImageViews[i] = imageView;
	}

	VkPhysicalDeviceProperties properties{};
	vkGetPhysicalDeviceProperties(pPhysicalDevice->getDeviceConst(), &properties);

	VkSamplerCreateInfo samplerInfo{};
	samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerInfo.magFilter = VK_FILTER_LINEAR;
	samplerInfo.minFilter = VK_FILTER_LINEAR;
	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.anisotropyEnable = VK_TRUE;
	samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
	samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	samplerInfo.unnormalizedCoordinates = VK_FALSE;
	samplerInfo.compareEnable = VK_FALSE;
	samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

	if (vkCreateSampler(pLogicalDevice->getDeviceConst(), &samplerInfo, nullptr, &m_textureSampler) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create texture sampler!");
	}
}


void  ZwTextureManager::destroy(ZwLogicalDevice* pLogicalDevice)
{
	if (!pLogicalDevice)
		return;

	if (m_images.size() != m_textureImageMemories.size())
		return;
	if (m_images.size() != m_textureImageViews.size())
		return;

	vkDestroySampler(pLogicalDevice->getDeviceConst(), m_textureSampler, nullptr);

	for (int i = 0; i < m_images.size(); i++)
	{
		vkDestroyImageView(pLogicalDevice->getDeviceConst(), m_textureImageViews[i], nullptr);
		vkDestroyImage(pLogicalDevice->getDeviceConst(), m_images[i], nullptr);
		vkFreeMemory(pLogicalDevice->getDeviceConst(), m_textureImageMemories[i], nullptr);
	}
}