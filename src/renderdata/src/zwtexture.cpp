#include <include/renderdata/zwtexture.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

ZwTexture::ZwTexture(const std::string& texturePath)
{
	if (texturePath.empty())
		return;

	m_pixels = stbi_load(texturePath.c_str(), &m_texWidth, &m_texHeight, &m_texChannels, STBI_rgb_alpha);

	if (!m_pixels)
		return;
}

void ZwTexture::freePixels()
{
	if (!m_pixels)
		return;
	stbi_image_free(m_pixels);
	m_pixels = nullptr;
}

ZwTexture::~ZwTexture()
{
	// freePixels();
}

//ZwTexture::ZwTexture(const ZwTexture& texture)
//{
//	need deepClone or move?
//}
