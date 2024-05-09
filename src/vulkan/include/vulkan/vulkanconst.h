#ifndef VULKANCONST_H
#define VULKANCONST_H
#include <vector>
#include <string>

constexpr const char* APP_NAME = "Zw Render";
constexpr const char* ENGINE_NAME = "Zw Engine";

const std::vector<const char*> VALIDATION_LAYERS = 
{
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> DEVICE_EXTENSIONS =
{
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const std::string VERTEXSHADERPATH = "../shader/triangle/trianglevert.spv";
const std::string FRAGMENTSHADERPATH = "../shader/triangle/trianglefrag.spv";

#ifdef NDEBUG
const bool ENABLEVALIDATIONLAYERS = false;
#else
const bool ENABLEVALIDATIONLAYERS = true;
#endif


#endif // !VULKANCONST_H
