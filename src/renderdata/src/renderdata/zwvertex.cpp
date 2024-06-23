#include <include/renderdata/zwvertex.h>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <stdexcept>
#include <unordered_map>


ZwVertex::ZwVertex(const glm::vec3& positon, const glm::vec3& color, const glm::vec3& normal, const glm::vec2& texCoord) : m_pos(positon), m_color(color), m_normal(normal), m_texCoord(texCoord)
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

void ZwVertex::setNormal(const glm::vec3& normal)
{
    if (m_normal == normal)
        return;
    m_normal = normal;
}

void ZwVertex::setTexCoord(const glm::vec2& texCoord)
{
	if (m_texCoord == texCoord)
		return;
	m_texCoord = texCoord;
}


void ZwObj::load(const std::string& loadPath)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, loadPath.c_str())) 
	{
		throw std::runtime_error(warn + err);
	}

    std::unordered_map<ZwVertex, uint32_t> uniqueVertices{};

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            ZwVertex vertex{};

            vertex.setPos({
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            });

            vertex.setTexCoord({
                attrib.texcoords[2 * index.texcoord_index + 0],
                1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            });

            vertex.setColor({ 1.0f, 1.0f, 1.0f });

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                vertices.push_back(vertex);
            }

            indices.push_back(uniqueVertices[vertex]);
        }
    }
}