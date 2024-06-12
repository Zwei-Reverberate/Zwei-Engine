#include <include/renderobject/zwrenderobjectmanager.h>

void ZwRenderObjectManager::prePareRenderObjects(ZwLogicalDevice* pLogicalDevice, ZwPhysicalDevice* pPhysicalDevice, ZwCommandManager* pCommandManager, const std::vector<SingleVertexData>& vertexDatas)
{
	if (!pLogicalDevice || !pPhysicalDevice || !pCommandManager)
		return;

	for (int i = 0; i < vertexDatas.size(); ++i)
	{
		std::unique_ptr<ZwRenderObject> pObject = std::make_unique<ZwRenderObject>();
		pObject->setUpVertexData(pLogicalDevice, pPhysicalDevice, pCommandManager, vertexDatas[i]);
		pObject->setUpPipelineId(0); // temp
		pObject->setUpDescriptorSetsId(i); // temp
		m_objectVec.emplace_back(std::move(pObject));
	}
}


void ZwRenderObjectManager::releaseObjects(ZwLogicalDevice* pLogicalDevice)
{
	if (!pLogicalDevice)
		return;
	for (int i = 0; i < m_objectVec.size(); ++i)
	{
		m_objectVec[i]->releaseBuffer(pLogicalDevice);
	}
}