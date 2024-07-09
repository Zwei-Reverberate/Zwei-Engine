#include <include/converter/meshconverter.h>


const std::vector<SingleVertexData> MeshConverter::parseVertexData(const std::unordered_map<ElementId, std::shared_ptr<SurfaceMesh>> renderMeshes)
{
	std::vector<SingleVertexData> res;
	if (renderMeshes.empty())
		return res;
	
	// 暂将每个 element 都分开绘制，后续在考虑合并
	for (auto& iter : renderMeshes)
	{
		res.emplace_back(parseSingleData(iter.second));
	}
	return res;
}


SingleVertexData MeshConverter::parseSingleData(std::shared_ptr<SurfaceMesh> pMesh)
{
	SingleVertexData data;
	if (!pMesh)
		return data;

    // Map to store vertex index mapping
    std::map<SurfaceMesh::Vertex_index, uint32_t> vertexIndexMap;
    uint32_t currentIndex = 0;

    // Extract vertex positions
    for (auto vertex : pMesh->vertices()) 
    {
        auto point = pMesh->point(vertex);
        glm::vec3 position(point.x(), point.y(), point.z());
        data.vertices.emplace_back(ZwVertex(position));
        vertexIndexMap[vertex] = currentIndex++;
    }

    // Compute normals for each face and assign to vertices
    for (auto face : pMesh->faces()) 
    {
        glm::vec3 normal(0.0f, 0.0f, 1.0f);
        SurfaceMesh::Halfedge_index he = pMesh->halfedge(face);
        SurfaceMesh::Vertex_index v1 = pMesh->target(he);
        SurfaceMesh::Vertex_index v2 = pMesh->target(pMesh->next(he));
        SurfaceMesh::Vertex_index v3 = pMesh->target(pMesh->next(pMesh->next(he)));

        glm::vec3 p1 = data.vertices[vertexIndexMap[v1]].getPos();
        glm::vec3 p2 = data.vertices[vertexIndexMap[v2]].getPos();
        glm::vec3 p3 = data.vertices[vertexIndexMap[v3]].getPos();

        glm::vec3 u = p2 - p1;
        glm::vec3 v = p3 - p1;
        normal = glm::normalize(glm::cross(u, v));
        if (normal == glm::vec3(.0))
        {
            assert(false);
        }

        data.vertices[vertexIndexMap[v1]].setNormal(normal);
        data.vertices[vertexIndexMap[v2]].setNormal(normal);
        data.vertices[vertexIndexMap[v3]].setNormal(normal);
    }

    // Extract indices
    for (auto face : pMesh->faces()) 
    {
        SurfaceMesh::Halfedge_index he = pMesh->halfedge(face);
        data.indices.push_back(vertexIndexMap[pMesh->target(he)]);
        data.indices.push_back(vertexIndexMap[pMesh->target(pMesh->next(he))]);
        data.indices.push_back(vertexIndexMap[pMesh->target(pMesh->next(pMesh->next(he)))]);
    }

	return data;
}