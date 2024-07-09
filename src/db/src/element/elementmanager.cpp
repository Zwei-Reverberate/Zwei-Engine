#include <include/element/elementmanager.h>

void ElementManager::deleteElement(const ElementId& id)
{
    for (auto& [category, idSet] : m_categoryMap) 
    {
        idSet.erase(id);
    }
    m_elementsMap.erase(id);
}


std::shared_ptr<Element> ElementManager::getElementById(const ElementId& id) const
{
    auto it = m_elementsMap.find(id);
    return it != m_elementsMap.end() ? it->second : nullptr;
}

std::shared_ptr<Element> ElementManager::cloneElement(const ElementId& id)
{
    auto it = m_elementsMap.find(id);
    if (it != m_elementsMap.end()) 
    {
        auto clonedElement = it->second->clone();
        clonedElement->setId(ElementId::createNewId());
        m_elementsMap[clonedElement->getId()] = clonedElement;
        m_categoryMap[clonedElement->getCategory()].insert(clonedElement->getId());
        return clonedElement;
    }
    return nullptr;
}


std::set<std::shared_ptr<Element>>  ElementManager::getRenderableElements() const
{
    std::set<std::shared_ptr<Element>> resSet;
    for (const auto& iter : m_elementsMap)
    {
        if (!iter.first.isValid() || !iter.second)
            continue;
        if (iter.second->isrRnderable())
            resSet.emplace(iter.second);
    }
    return resSet;
}

std::set<ElementId> ElementManager::getElementsByCategory(ElementCategory category) const
{
    auto it = m_categoryMap.find(category);
    return it != m_categoryMap.end() ? it->second : std::set<ElementId>{};
}