#include <include/element/element.h>

Element::Element() : m_id(ElementId()) {}

std::shared_ptr<Element> Element::clone()
{
	auto pClone = std::make_shared<Element>();
	return pClone;
}

Element::~Element()
{
	int test = 0;
}