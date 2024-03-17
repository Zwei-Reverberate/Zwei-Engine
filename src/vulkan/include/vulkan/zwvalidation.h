#ifndef ZWVALIDATION_H
#define ZWVALIDATION_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

class ZwInstance;
class ZwValidation
{

public:
    void init(const ZwInstance* pInstance);
    void destroy(const ZwInstance* pInstance);

public:
    // 检查所有的 validation layers 是否可用
    static bool checkValidationLayerSupport();

    // 根据是否启用 validation layers 返回需要的 extension 列表
    static std::vector<const char*> getRequiredExtensions();

    // 接受调试信息的回调函数
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback
    (
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    );

    static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    static VkResult CreateDebugUtilsMessengerEXT
    (
        const ZwInstance* pInstance,
        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkDebugUtilsMessengerEXT* pDebugMessenger
    );

    static void DestroyDebugUtilsMessengerEXT
    (
        const ZwInstance* pInstance,
        VkDebugUtilsMessengerEXT debugMessenger,
        const VkAllocationCallbacks* pAllocator
    );

private:
    VkDebugUtilsMessengerEXT* m_pDebugMessenger = nullptr; // 用于存储回调函数信息
};

#endif // !ZWVALIDATION_H
