#ifndef VULKANCONST_H
#define VULKANCONST_H
#include <vector>

constexpr const char* APP_NAME = "Zw Render";
constexpr const char* ENGINE_NAME = "Zw Engine";

const std::vector<const char*> VALIDATION_LAYERS = 
{
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool ENABLEVALIDATIONLAYERS = false;
#else
const bool ENABLEVALIDATIONLAYERS = true;
#endif


#endif // !VULKANCONST_H
