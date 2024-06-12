#ifndef ZWRENDEROBJECTMANAGER_H
#define ZWRENDEROBJECTMANAGER_H
#include <include/renderobject/zwrenderobject.h>
#include <vector>

class ZwRenderObjectManager
{
public:
	void prePareRenderObjects(ZwLogicalDevice* pLogicalDevice, ZwPhysicalDevice* pPhysicalDevice, ZwCommandManager* pCommandManager, const std::vector<SingleVertexData>& vertexDatas);
	void releaseObjects(ZwLogicalDevice* pLogicalDevice);

	const std::vector<std::unique_ptr<ZwRenderObject>>& getRenderObjects() const { return m_objectVec; }

private:
	std::vector<std::unique_ptr<ZwRenderObject>> m_objectVec{};
};


#endif // !ZWRENDEROBJECTMANAGER_H
