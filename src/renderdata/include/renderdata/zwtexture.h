#ifndef ZWTEXTURE_H
#define ZWTEXTURE_H
#include <string>

typedef unsigned char stbi_uc;
class ZwTexture
{
public:
	ZwTexture() = default;
	ZwTexture(const std::string& texturePath);
	//ZwTexture(const ZwTexture& texture);
	~ZwTexture();

	int getTexWidth() const { return m_texWidth; }
	int getTexHeight() const { return m_texHeight; }
	int getTexChannels() const { return m_texChannels; }
	stbi_uc* getPixels() const { return m_pixels; }

	void freePixels();

private:
	int m_texWidth = 0;
	int m_texHeight = 0;
	int m_texChannels = 0;
	stbi_uc* m_pixels = nullptr;
};

#endif // !ZWTEXTURE_H
