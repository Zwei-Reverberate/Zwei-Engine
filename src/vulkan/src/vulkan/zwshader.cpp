#include <include/vulkan/zwshader.h>
#include <fstream>
#include <stdexcept>


std::vector<char> ZwShader::readFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
}

void ZwShader::createShaderModule(const std::vector<char>& code, ZwLogicalDevice* pLogicalDevice)
{
    if (!pLogicalDevice || code.empty())
        return;
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    if (vkCreateShaderModule(pLogicalDevice->getDevice(), &createInfo, nullptr, &m_shaderModule) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create shader module!");
    }
}

void ZwShader::init(const std::string& filename, ZwLogicalDevice* pLogicalDevice, ShaderType type)
{
    if (!pLogicalDevice)
        return;
    std::vector<char> shaderCode = readFile(filename);
    createShaderModule(shaderCode, pLogicalDevice);
    m_shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    if (type == ShaderType::VERTEX)
    {
        m_shaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    }
    else if (type == ShaderType::FRAGMENT)
    {
        m_shaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    }
    else
    {
        return;
    }
    m_shaderStageInfo.module = m_shaderModule;
    m_shaderStageInfo.pName = "main"; void destroy(ZwLogicalDevice * pLogicalDevice);
}

void ZwShader::destroy(ZwLogicalDevice* pLogicalDevice)
{
    if (!pLogicalDevice)
        return;
    vkDestroyShaderModule(pLogicalDevice->getDevice(), m_shaderModule, nullptr);
}