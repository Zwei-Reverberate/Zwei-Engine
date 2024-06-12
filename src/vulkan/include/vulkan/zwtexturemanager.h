#ifndef ZWTEXTUREMANAGER_H
#define ZWTEXTUREMANAGER_H
#include <include/vulkan/zwlogicaldevice.h>
#include <vector>

class ZwTexture;
class ZwCommandManager;
class ZwTextureManager
{
public:
	ZwTextureManager() = default;
	void init(std::vector<ZwTexture>& textures, ZwPhysicalDevice* pPhysicalDevice, ZwLogicalDevice* pLogicalDevice, ZwCommandManager* pCommandManager);
	void destroy(ZwLogicalDevice* pLogicalDevice);

	const VkSampler& getTextureSampler() const { return m_textureSampler; }
	const std::vector<VkImageView>& getImageViews() const { return m_textureImageViews; }

private:
	std::vector<VkImage> m_images;
	std::vector<VkDeviceMemory> m_textureImageMemories;
	std::vector<VkImageView> m_textureImageViews;
	VkSampler m_textureSampler;
};


#endif // !ZWTEXTUREMANAGER_H
