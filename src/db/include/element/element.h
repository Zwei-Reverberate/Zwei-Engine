#ifndef ELEMENT_H
#define ELEMENT_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/\Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <include/element/elementcategory.h>
#include <include/element/elementid.h>
#include <string>
#include <tuple>
#include <memory>

typedef CGAL::Simple_cartesian<double> KernelType;
//typedef CGAL::Exact_predicates_inexact_constructions_kernel KernelType;
typedef KernelType::Point_3 Point3D;
typedef KernelType::Vector_3 Vector3D;
typedef CGAL::Surface_mesh<Point3D> SurfaceMesh;

class ElementManager;
class Element
{
    friend class ElementManager;
public:
    Element();
    ElementId getId() const { return m_id; }
    static constexpr auto getMetadata()
    {
        return std::make_tuple
        (
            std::make_pair("id", &Element::m_id)
        );
    }

    virtual ~Element();
    virtual ElementCategory getCategory() const { return ElementCategory::DEFAULT; }
    virtual bool isrRnderable() { return false; }
    virtual std::shared_ptr<SurfaceMesh> buildMesh() { return nullptr; }
   
private:
    void setId(const ElementId& id) { m_id = id; }
    virtual std::shared_ptr<Element> clone();

private:
    ElementId m_id;
};

#endif // ELEMENT_H
