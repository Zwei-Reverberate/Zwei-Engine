#include <include/element/element.h>

Element::Element() : m_id(ElementId()) {}

Element* Element::clone() 
{
	Element* pClone = new Element();
	return pClone;
}