#include <include/vulkan/zwphysicaldevice.h>
#include <include/vulkan/zwqueuefamilyindices.h>
#include <include/vulkan/zwsurface.h>
#include <stdexcept>
#include <vector>

void  ZwPhysicalDevice::init(const ZwInstance* pInstance, const ZwSurface* pSurface)
{
	if (!pInstance || !pSurface)
		return;

    // �����г��Կ��豸���Ӳ�ѯ��ſ�ʼ�����豸��Ϊ0�����׳��쳣
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(pInstance->getInstance(), &deviceCount, nullptr);
    if (deviceCount == 0)
    {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    // �������һ���������������е� VkPhysicalDevice handle
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(pInstance->getInstance(), &deviceCount, devices.data());

    for (const auto& device : devices)
    {
        // �鿴�����Ӳ����Ϣ
        // VkPhysicalDeviceProperties deviceProperties;
        // vkGetPhysicalDeviceProperties(device, &deviceProperties);
        if (ZwQueueFamilyIndices::isDeviceSuitable(device, pSurface->getSurface()))
        {
            m_PhysicalDevice = device; // ѡ����������ĵ�һ���Կ�
            break;
        }
    }

    if (m_PhysicalDevice == VK_NULL_HANDLE)
    {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}