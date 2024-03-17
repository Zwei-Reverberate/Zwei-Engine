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
    // ������е� validation layers �Ƿ����
    static bool checkValidationLayerSupport();

    // �����Ƿ����� validation layers ������Ҫ�� extension �б�
    static std::vector<const char*> getRequiredExtensions();

    // ���ܵ�����Ϣ�Ļص�����
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
    VkDebugUtilsMessengerEXT* m_pDebugMessenger = nullptr; // ���ڴ洢�ص�������Ϣ
};

#endif // !ZWVALIDATION_H
