#ifndef ZWRENDEROBJECT_H
#define ZWRENDEROBJECT_H
#include <memory>
#include <include/vulkan/vulkanconst.h>
#include <include/renderdata/zwvertex.h>
#include <include/renderobject/zwtoolid.h>
#include <include/vulkan/zwvulkantype.h>
#include <include/vulkan/zwvertexbuffer.h>
#include <include/vulkan/zwindexbuffer.h>

class ZwLogicalDevice;
class ZwPhysicalDevice;
class ZwCommandManager;
class ZwRenderObject
{
public:
	ZwRenderObject() = default;
	void setUpVertexData(ZwLogicalDevice* pLogicalDevice, ZwPhysicalDevice* pPhysicalDevice, ZwCommandManager* pCommandManager, const SingleVertexData& vertexData);
	void setUpPipelineId(const ZwToolId& id);
	void setUpDescriptorSetsId(const ZwToolId& id);
	void releaseBuffer(ZwLogicalDevice* pLogicalDevice);

	const VkBuffer& getVertexBuffer() const { return m_pVertexBuffer->getVertexBuffer(); }
	const VkBuffer& getIndexBuffer() const { return m_pIndexBuffer->getIndexBuffer(); }
	int getIndexSize() const { return m_pIndexBuffer->getIndexSize(); }
	const ZwToolId& getPipeLineId() const { return m_pipelineId; }
	const ZwToolId& getDescriptorSetsId() const { return m_descriptorSetsId; }

private:
	// unique
	std::unique_ptr<ZwVertexBuffer> m_pVertexBuffer = nullptr;
	std::unique_ptr<ZwIndexBuffer> m_pIndexBuffer = nullptr;

	// shared
	ZwToolId m_pipelineId { INVALID_TOOL_ID };
	ZwToolId m_descriptorSetsId{ INVALID_TOOL_ID };
};


#endif // !ZWRENDEROBJECT_H
