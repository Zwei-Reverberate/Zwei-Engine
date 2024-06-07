#ifndef ZWVERTEX_H
#define ZWVERTEX_H
#include <glm/glm.hpp>
#include <vector>

class ZwVertex
{
public:
	ZwVertex() = default;
	ZwVertex(const glm::vec3& positon, const glm::vec3& color = glm::vec3(0, 0, 0), const glm::vec2& texCoord = glm::vec2(0, 0));

	const glm::vec3& getPos() const { return m_pos; }
	void setPos(const glm::vec3& position);
	static uint32_t getPosOffset() { return  offsetof(ZwVertex, ZwVertex::m_pos); }

	const glm::vec3& getColor() const { return m_color; }
	void setColor(const glm::vec3& color);
	static uint32_t getColorOffset() { return  offsetof(ZwVertex, ZwVertex::m_color); }

	const glm::vec2& getTexCoord() const { return m_texCooord; }
	void setTexCoord(const glm::vec2& texCoord);
	static uint32_t getTexCoordOffset() { return  offsetof(ZwVertex, ZwVertex::m_texCooord); }

private:
	glm::vec3 m_pos{ 0, 0, 0 };
	glm::vec3 m_color{ 0, 0, 0 };
	glm::vec2 m_texCooord{ 0, 0 };
};


// temp
const std::vector<ZwVertex> zwVertices =
{
	ZwVertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
	ZwVertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)),
	ZwVertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)),
	ZwVertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
};

const std::vector<uint16_t> zwIndices = 
{
	0, 1, 2, 2, 3, 0
};

#endif