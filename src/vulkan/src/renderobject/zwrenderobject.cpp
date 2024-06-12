#include <include/renderobject/zwrenderobject.h>
#include <include/vulkan/zwvertexbuffer.h>
#include <include/vulkan/zwindexbuffer.h>

void ZwRenderObject::setUpVertexData(ZwLogicalDevice* pLogicalDevice, ZwPhysicalDevice* pPhysicalDevice, ZwCommandManager* pCommandManager, const SingleVertexData& vertexData)
{
	if (!pLogicalDevice || !pPhysicalDevice || !pCommandManager)
		return;

	m_pVertexBuffer = std::make_unique<ZwVertexBuffer>();
	m_pVertexBuffer->init(pLogicalDevice, pPhysicalDevice, pCommandManager, vertexData.vertices);

	m_pIndexBuffer = std::make_unique<ZwIndexBuffer>();
	m_pIndexBuffer->init(pLogicalDevice, pPhysicalDevice, pCommandManager, vertexData.indices);
}

void ZwRenderObject::setUpPipelineId(const ZwToolId& id)
{
	m_pipelineId = id;
}

void ZwRenderObject::setUpDescriptorSetsId(const ZwToolId& id)
{
	m_descriptorSetsId = id;
}

void ZwRenderObject::releaseBuffer(ZwLogicalDevice* pLogicalDevice)
{
	if (!pLogicalDevice)
		return;
	if (m_pVertexBuffer)
		m_pVertexBuffer->destroy(pLogicalDevice);
	if (m_pIndexBuffer)
		m_pIndexBuffer->destroy(pLogicalDevice);

	m_pipelineId = INVALID_TOOL_ID;
	m_descriptorSetsId = INVALID_TOOL_ID;
}