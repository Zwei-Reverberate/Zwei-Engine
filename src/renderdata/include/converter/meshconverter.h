#ifndef MESHCONVERTER_H
#define MESHCONVERTER_H

#include <include/converter/zwvulkantype.h>
#include <include/scene/scene.h>
#include <vector>

class MeshConverter
{
public:
	// 暂时静态，后续考虑在这里缓存顶点数据
	static const std::vector<SingleVertexData> parseVertexData(const std::unordered_map<ElementId, std::shared_ptr<SurfaceMesh>> renderMeshes);

	static SingleVertexData parseSingleData(std::shared_ptr<SurfaceMesh> pMesh);
};

#endif // !MESHCONVERTER_H
