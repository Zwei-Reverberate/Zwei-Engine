#include <include/scene/scene.h>

#include <include/geometry/basicshape/cuboid.h>

void Scene::init()
{
	initRenderMeshes();

	auto p1 = ElementManager::getManager()->createElement<Cuboid>();
	p1->setLength(1);
	p1->setWidth(1);
	p1->setHeight(1);
	p1->setPosition(glm::vec3(1, 1, 1));

	{
		auto pe = ElementManager::getManager()->cloneElement(p1->getId());
		Cuboid* p2 = dynamic_cast<Cuboid*>(pe.get());
		p2->setPosition(glm::vec3(-1, -1, -1));

		markElementDirty(p1->getId());
		markElementDirty(p2->getId());
		updateDirtyElements();
	}
}

std::set<std::shared_ptr<Element>> Scene::collectRenderElements()
{
	std::set < std::shared_ptr<Element>> res;
	ElementManager* pEleMgr = ElementManager::getManager();
	if (!pEleMgr)
		return res;
	return pEleMgr->getRenderableElements();
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
		if (!pEle->isrRnderable()) // temp
			continue;
		std::shared_ptr<SurfaceMesh> pMesh = pEle->buildMesh();


		auto findIt = m_renderMeshes.find(id);
		if (findIt != m_renderMeshes.end())
		{
			if (findIt->second == nullptr)
			{
				findIt->second = pMesh;
			}
			else
			{
				auto oldMesh = findIt->second;
				oldMesh.reset();
				findIt->second = pMesh;
			}
		}
		else
		{
			m_renderMeshes.emplace(pEle->getId(), pMesh);
		}
	}
}

void Scene::resetDirtyElements()
{
	m_dirtyElements.clear();
}


void Scene::initRenderMeshes()
{
	const std::set<std::shared_ptr<Element>>& renderElements = collectRenderElements();
	for (const auto& iter : renderElements)
	{
		if (!iter)
			continue;
		m_renderMeshes.emplace(iter->getId(), nullptr);
	}
}


void Scene::cleanUp()
{
}