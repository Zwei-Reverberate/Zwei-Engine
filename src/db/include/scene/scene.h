#ifndef SCENE_H
#define SCENE_H
#include <include/element/elementmanager.h>

class Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    void init();

    void cleanUp();
    
    void markElementDirty(const ElementId& id);

    void resetDirtyElements();

    void updateDirtyElements();

    const std::set<ElementId>& getDirtyElements() const { return m_dirtyElements; }

    const std::unordered_map<ElementId, std::shared_ptr<SurfaceMesh>>& getRenderMeshes() const { return m_renderMeshes; }

private:
    void initRenderMeshes();
    std::set<std::shared_ptr<Element>> collectRenderElements();

private:
    std::set<ElementId> m_dirtyElements;
    std::unordered_map<ElementId, std::shared_ptr<SurfaceMesh>> m_renderMeshes;
};


#endif