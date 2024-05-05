#include <include/vulkan/zwphysicaldevice.h>
#include <include/vulkan/zwqueuefamilyindices.h>
#include <include/vulkan/zwsurface.h>
#include <stdexcept>
#include <vector>

void  ZwPhysicalDevice::init(const ZwInstance* pInstance, const ZwSurface* pSurface)
{
	if (!pInstance || !pSurface)
		return;

    // 首先列出显卡设备。从查询编号开始。若设备数为0，则抛出异常
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(pInstance->getInstanceConst(), &deviceCount, nullptr);
    if (deviceCount == 0)
    {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    // 否则分配一个数组来保存所有的 VkPhysicalDevice handle
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(pInstance->getInstanceConst(), &deviceCount, devices.data());

    for (const auto& device : devices)
    {
        if (ZwQueueFamilyIndices::isDeviceSuitable(device, pSurface->getSurfaceConst()))
        {
            m_PhysicalDevice = device; // 选择满足需求的第一张显卡
            break;
        }
    }

    if (m_PhysicalDevice == VK_NULL_HANDLE)
    {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}