#include <include/graphic/graphicelement.h>
#include <CGAL/Surface_mesh.h>

GraphicElement::GraphicElement() :Element()
{	
};

std::shared_ptr<Element> GraphicElement::clone()
{
	auto pClone = std::make_shared<GraphicElement>();
	pClone->setPosition(getPosition());
	return pClone;
}

void  GraphicElement::setPosition(const glm::vec3& position)
{
	if (m_position == position)
		return;
	m_position = position;
}