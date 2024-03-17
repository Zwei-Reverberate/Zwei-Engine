#include <include/vulkan/zwvalidation.h>
#include <include/vulkan/vulkanconst.h>
#include <include/vulkan/zwinstance.h>
#include <stdexcept>
#include <iostream>


void ZwValidation::init(const ZwInstance* pInstance)
{
    if (!pInstance || !ENABLEVALIDATIONLAYERS)
        return;

    m_pDebugMessenger = new VkDebugUtilsMessengerEXT();

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    populateDebugMessengerCreateInfo(createInfo);

    if (CreateDebugUtilsMessengerEXT(pInstance, &createInfo, nullptr, m_pDebugMessenger) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to set up debug messenger!");
    }
}

void ZwValidation::destroy(const ZwInstance* pInstance)
{
    if (!pInstance)
        return;
    if (ENABLEVALIDATIONLAYERS && m_pDebugMessenger)
    {
        DestroyDebugUtilsMessengerEXT(pInstance, *m_pDebugMessenger, nullptr);
    }
}

void ZwValidation::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
    createInfo.pUserData = nullptr; // Optional
}

bool ZwValidation::checkValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : VALIDATION_LAYERS)
    {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers)
        {
            if (strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }
        if (!layerFound)
        {
            return false;
        }
    }
    return true;
}

std::vector<const char*> ZwValidation::getRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (ENABLEVALIDATIONLAYERS)
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    return extensions;
}


VKAPI_ATTR VkBool32 VKAPI_CALL ZwValidation::debugCallback
(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData
)
{
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}

VkResult ZwValidation::CreateDebugUtilsMessengerEXT
(
    const ZwInstance* pInstance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger
)
{
    if(!pInstance)
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(*pInstance->getInstanceConst(), "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        return func(*pInstance->getInstanceConst(), pCreateInfo, pAllocator, pDebugMessenger);
    }
    else
    {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void ZwValidation::DestroyDebugUtilsMessengerEXT
(
    const ZwInstance* pInstance,
    VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks* pAllocator
)
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(*pInstance->getInstanceConst(), "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        func(*pInstance->getInstanceConst(), debugMessenger, pAllocator);
    }
}