#ifndef ZWDEPTHRESOURCES_H
#define ZWDEPTHRESOURCES_H
#include <include/vulkan/zwlogicaldevice.h>

class ZwSwapChain;
class ZwDepthResources
{
public:
    void init(ZwLogicalDevice* pLogicalDevice, ZwPhysicalDevice* pPhysicalDevice, ZwSwapChain* pSwapChain);
    void destroy(ZwLogicalDevice* pLogicalDevice);

    const VkImageView& getDepthImageView() const {return m_depthImageView;}

private:
    VkImage m_depthImage;
    VkDeviceMemory m_depthImageMemory;
    VkImageView m_depthImageView;
};


#endif
