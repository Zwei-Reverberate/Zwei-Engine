#ifndef ZWVERTEX_H
#define ZWVERTEX_H
#include <glm/glm.hpp>
#include <vector>

class ZwVertex
{
public:
	ZwVertex(const glm::vec3& positon, const glm::vec3& color = glm::vec3(0, 0, 0));

	const glm::vec3& getPos() const { return m_pos; }
	void setPos(const glm::vec3& position);
	static uint32_t getPosOffset() { return  offsetof(ZwVertex, ZwVertex::m_pos); }

	const glm::vec3& getColor() const { return m_color; }
	void setColor(const glm::vec3& color);
	static uint32_t getColorOffset() { return  offsetof(ZwVertex, ZwVertex::m_color); }

private:
	glm::vec3 m_pos;
	glm::vec3 m_color;
};


// temp
const std::vector<ZwVertex> zwVertices =
{
	ZwVertex(glm::vec3(0.0f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)),
	ZwVertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
	ZwVertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
};

#endif