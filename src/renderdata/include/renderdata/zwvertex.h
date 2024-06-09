#ifndef ZWVERTEX_H
#define ZWVERTEX_H
#include <glm/glm.hpp>
#include <vector>
#include <string>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

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

	const glm::vec2& getTexCoord() const { return m_texCoord; }
	void setTexCoord(const glm::vec2& texCoord);
	static uint32_t getTexCoordOffset() { return  offsetof(ZwVertex, ZwVertex::m_texCoord); }

	bool operator==(const ZwVertex& other) const { return m_pos == other.m_pos && m_color == other.m_color && m_texCoord == other.m_texCoord; };

private:
	glm::vec3 m_pos{ 0, 0, 0 };
	glm::vec3 m_color{ 0, 0, 0 };
	glm::vec2 m_texCoord{ 0, 0 };
};

namespace std {
	template<> struct hash<ZwVertex> {
		size_t operator()(ZwVertex const& vertex) const {
			return ((hash<glm::vec3>()(vertex.getPos()) ^ (hash<glm::vec3>()(vertex.getColor()) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.getTexCoord()) << 1);
		}
	};
}


// temp
class ZwObj
{
public:
	void load(const std::string& loadPath);

public:
	std::vector<ZwVertex> vertices;
	std::vector<uint32_t> indices;
};


// temp
const std::vector<ZwVertex> zwVertices =
{
	ZwVertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
	ZwVertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)),
	ZwVertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)),
	ZwVertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)),

	ZwVertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
	ZwVertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)),
	ZwVertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)),
	ZwVertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
};

const std::vector<uint16_t> zwIndices = 
{
	0, 1, 2, 2, 3, 0,
	4, 5, 6, 6, 7, 4
};


#endif