#include <include/renderdata/zwvertex.h>

ZwVertex::ZwVertex(const glm::vec3& positon, const glm::vec3& color, const glm::vec2& texCoord) : m_pos(positon), m_color(color), m_texCooord(texCoord)
{
}

void ZwVertex::setPos(const glm::vec3& position)
{
	if (m_pos == position)
		return;
	m_pos = position;
}

void ZwVertex::setColor(const glm::vec3& color)
{
	if (m_color == color)
		return;
	m_color = color;
}

void ZwVertex::setTexCoord(const glm::vec2& texCoord)
{
	if (m_texCooord == texCoord)
		return;
	m_texCooord = texCoord;
}