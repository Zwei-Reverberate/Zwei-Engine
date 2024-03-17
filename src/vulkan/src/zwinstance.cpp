#include <include/vulkan/zwinstance.h>
#include <include/vulkan/vulkanconst.h>
#include <include/vulkan/zwvalidation.h>
#include <stdexcept>

void ZwInstance::init()
{
    m_pInstance = new VkInstance();

    // 在创建之前检查所有的 validation layers 是否可用
    if (ENABLEVALIDATIONLAYERS && !ZwValidation::checkValidationLayerSupport())
    {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = APP_NAME;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = ENGINE_NAME;
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = ZwValidation::getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();


    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (ENABLEVALIDATIONLAYERS)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(VALIDATION_LAYERS.size());
        createInfo.ppEnabledLayerNames = VALIDATION_LAYERS.data();
        ZwValidation::populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else
    {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }

    if (vkCreateInstance(&createInfo, nullptr, m_pInstance) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create instance!");
    }
}

void ZwInstance::destroy()
{
    if (!m_pInstance)
        return;
    vkDestroyInstance(*m_pInstance, nullptr);

    delete m_pInstance;
    m_pInstance = nullptr;
}