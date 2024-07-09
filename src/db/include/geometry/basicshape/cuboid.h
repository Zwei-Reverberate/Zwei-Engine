#ifndef CUBOID_H
#define CUBOID_H

#include <include/graphic/graphicelement.h>

class Cuboid : public GraphicElement
{
public:
	Cuboid();
	virtual ElementCategory getCategory()  const override { return ElementCategory::CUBOID; }
	static constexpr auto getMetadata()
	{
		return std::tuple_cat
		(
			GraphicElement::getMetadata(),
			std::make_tuple
			(
				std::make_pair("length", &Cuboid::m_length),
				std::make_pair("width", &Cuboid::m_width),
				std::make_pair("height", &Cuboid::m_height)
			)
		);
	}

	virtual std::shared_ptr<SurfaceMesh> buildMesh() override;

	double getLength() const { return m_length; }
	void setLength(double length);

	double getWidth() const { return m_width; }
	void setWidth(double width);

	double getHeight() const { return m_height; }
	void setHeight(double height);

private:
	virtual std::shared_ptr<Element> clone() override;

private:
	double m_length{ .0 };
	double m_width{ .0 };
	double m_height{ .0 };
};


#endif // CUBOID_H