#include <include/scene/scene.h>

void Scene::collectRenderElements()
{
	ElementManager* pEleMgr = ElementManager::getManager();
	if (!pEleMgr)
		return;
	pEleMgr->getRenderableElements();
}

void Scene::markElementDirty(const ElementId& id)
{
	ElementManager* pEleMgr = ElementManager::getManager();
	if (!pEleMgr)
		return;
	if (!id.isValid())
		return;
	if (m_dirtyElements.find(id) != m_dirtyElements.end())
		return;
	std::shared_ptr<Element> pEle = pEleMgr->getElementById(id);

	m_dirtyElements.emplace(id);
}

void Scene::updateDirtyElements()
{
	ElementManager* pEleMgr = ElementManager::getManager();
	if (!pEleMgr)
		return;
	if (m_dirtyElements.empty())
		return;
	for (const auto id : m_dirtyElements)
	{
		std::shared_ptr<Element> pEle = pEleMgr->getElementById(id);
		if (!pEle)
			continue;
		// to do: pEle 更新形体
	}
}

void Scene::resetDirtyElements()
{
	m_dirtyElements.clear();
}