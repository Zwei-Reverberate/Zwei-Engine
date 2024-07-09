#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H

#include <include/element/element.h>
#include <glm/glm.hpp>

class GraphicElement : public Element
{
public:
	GraphicElement();
	static constexpr auto getMetadata()
	{
		return std::tuple_cat
		(
			Element::getMetadata(),
			std::make_tuple
			(
				std::make_pair("position", &GraphicElement::m_position)
			)
		);
	}

	virtual ElementCategory getCategory()  const override { return ElementCategory::GRAPHIC; }
	virtual bool isrRnderable() override { return true; }
	
	void setPosition(const glm::vec3& position);
	const glm::vec3& getPosition() const { return m_position; };

private:
	virtual std::shared_ptr<Element> clone() override;

private:
	glm::vec3 m_position{ .0 };
};

#endif // !GRAPHICELEMENT_H
