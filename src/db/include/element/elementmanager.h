#ifndef ELEMENT_MANAGER_H
#define ELEMENT_MANAGER_H

#include <include/element/elementcategory.h>
#include <include/element/element.h>
#include <unordered_map>
#include <memory>
#include <set>

class ElementManager 
{
public:
    static ElementManager* getManager()
    {
        static ElementManager instance;
        return &instance;
    }

    template<typename T, typename... Args>
    std::shared_ptr<T> createElement(Args&&... args)
    {
        static_assert(std::is_base_of<Element, T>::value, "T must be derived from Element");
        auto element = std::make_shared<T>(std::forward<Args>(args)...);
        element->setId(ElementId::createNewId());
        m_elementsMap[element->getId()] = element;
        m_categoryMap[element->getCategory()].insert(element->getId());
        return element;
    }

    void deleteElement(const ElementId& id);

    std::shared_ptr<Element> cloneElement(const ElementId& id);

    std::shared_ptr<Element> getElementById(const ElementId& id) const;

    std::set<ElementId> getElementsByCategory(ElementCategory category) const;

    std::set<std::shared_ptr<Element>> getRenderableElements() const;

private:
    ElementManager() = default;
    ~ElementManager() = default;
    ElementManager(const ElementManager&) = delete;
    ElementManager& operator=(const ElementManager&) = delete;

private:
    std::unordered_map<ElementId, std::shared_ptr<Element>> m_elementsMap;
    std::unordered_map<ElementCategory, std::set<ElementId>> m_categoryMap;
};

#endif // ELEMENT_MANAGER_H
