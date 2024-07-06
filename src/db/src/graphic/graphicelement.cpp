#include <include/graphic/graphicelement.h>
#include <CGAL/Surface_mesh.h>

GraphicElement::GraphicElement() :Element()
{	
};

Element* GraphicElement::clone()
{
	GraphicElement* pClone = new GraphicElement();
	pClone->setPosition(m_position);
	return pClone;
}

void  GraphicElement::setPosition(const glm::vec3& position)
{
	if (m_position == position)
		return;
	m_position = position;
}