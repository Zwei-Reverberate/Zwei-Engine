#ifndef ZWSHADER_H
#define ZWSHADER_H
#include <include/vulkan/zwlogicaldevice.h>
#include <vector>
#include <string>

enum class ShaderType
{
	VERTEX = 0,
	FRAGMENT,
};


class ZwShader
{
public:
	static std::vector<char> readFile(const std::string& filename);
	void init(const std::string& filename, ZwLogicalDevice* pLogicalDevice, ShaderType type);
	void createShaderModule(const std::vector<char>& code, ZwLogicalDevice* pLogicalDevice);
	void destroy(ZwLogicalDevice* pLogicalDevice);
	const VkPipelineShaderStageCreateInfo& getShaderStageInfo() const { return m_shaderStageInfo; }

private:
	VkShaderModule m_shaderModule;
	VkPipelineShaderStageCreateInfo m_shaderStageInfo;
};

#endif // !ZWSHADER_H
