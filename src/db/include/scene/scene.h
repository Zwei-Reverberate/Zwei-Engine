#ifndef SCENE_H
#define SCENE_H
#include <include/element/elementmanager.h>

class Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    void collectRenderElements();
    
    void markElementDirty(const ElementId& id);

    void resetDirtyElements();

    void updateDirtyElements();

private:
    std::set<ElementId> m_dirtyElements;
};


#endif