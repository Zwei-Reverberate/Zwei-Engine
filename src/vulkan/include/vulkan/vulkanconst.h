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

const std::string VERTEXSHADERPATH = "../shader/texture/texturevert.spv";
const std::string FRAGMENTSHADERPATH = "../shader/texture/texturefrag.spv";

const std::string TEAR_IMAGE_PATH = "../resources/images/tear.jpg";

const int MAX_FRAMES_IN_FLIGHT = 2;

#ifdef NDEBUG
const bool ENABLEVALIDATIONLAYERS = false;
#else
const bool ENABLEVALIDATIONLAYERS = true;
#endif


#endif // !VULKANCONST_H
