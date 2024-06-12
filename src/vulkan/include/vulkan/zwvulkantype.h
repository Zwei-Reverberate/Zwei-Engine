#ifndef ZWVULKANTYPE_H
#define ZWVULKANTYPE_H
#include <string>
#include <vector>
#include <include/renderdata/zwvertex.h>

struct ShaderPath
{
	std::string vertexShaserPath;
	std::string fragmentShaderPath;
};

struct SingleVertexData
{
	std::vector<ZwVertex> vertices;
	std::vector<uint32_t> indices;
};


#endif // !ZWVULKANTYPE_H
