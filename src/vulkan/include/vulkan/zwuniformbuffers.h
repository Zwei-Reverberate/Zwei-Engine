#ifndef ZWUNIFORMBUFFERS_H
#define ZWUNIFORMBUFFERS_H
#include <include/vulkan/zwlogicaldevice.h>
#include <vector>

class ZwUniformBuffers
{
public:
    void init(ZwLogicalDevice* pLogicalDevice, ZwPhysicalDevice* pPhysicalDevice);
    void destroy(ZwLogicalDevice* pLogicalDevice);
    const std::vector<void*>& getUniformBuffersMapped() const { return m_uniformBuffersMapped; }
    const std::vector<VkBuffer>& getUniformBuffers() const { return m_uniformBuffers; }

private:
    std::vector<VkBuffer> m_uniformBuffers;
    std::vector<VkDeviceMemory> m_uniformBuffersMemory;
    std::vector<void*> m_uniformBuffersMapped;
};

#endif // !ZWUNIFORMBUFFERS_H
