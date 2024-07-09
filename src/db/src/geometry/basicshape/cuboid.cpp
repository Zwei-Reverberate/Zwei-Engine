#include <include/geometry/basicshape/cuboid.h>
#include <include/math/zwoperationutils.h>

Cuboid::Cuboid() : GraphicElement()
{
}

std::shared_ptr<Element> Cuboid::clone()
{
	auto pClone = std::make_shared<Cuboid>();
	pClone->setPosition(getPosition());
	pClone->setLength(getLength());
	pClone->setWidth(getWidth());
	pClone->setHeight(getHeight());
	return pClone;
}


void Cuboid::setLength(double length)
{
	if (ZwOperationUtils::isEqual(m_length, length))
		return;
	m_length = length;
}

void Cuboid::setWidth(double width)
{
	if (ZwOperationUtils::isEqual(m_width, width))
		return;
	m_width = width;
}

void Cuboid::setHeight(double height)
{
	if (ZwOperationUtils::isEqual(m_height, height))
		return;
	m_height = height;
}

std::shared_ptr<SurfaceMesh> Cuboid::buildMesh()
{
	std::shared_ptr<SurfaceMesh> pMesh = std::make_shared<SurfaceMesh>();

	glm::vec3 position = getPosition();
	Point3D center(position.x, position.y, position.z);

	double halfLength = getLength() / 2;
	double halfWidth = getWidth() / 2;
	double halfHeight = getHeight() / 2;

	auto v0 = pMesh->add_vertex(Point3D(center.x() - halfLength, center.y() - halfHeight, center.z() + halfWidth));
	auto v1 = pMesh->add_vertex(Point3D(center.x() - halfLength, center.y() - halfHeight, center.z() - halfWidth));
	auto v2 = pMesh->add_vertex(Point3D(center.x() + halfLength, center.y() - halfHeight, center.z() - halfWidth));
	auto v3 = pMesh->add_vertex(Point3D(center.x() + halfLength, center.y() - halfHeight, center.z() + halfWidth));

	auto v4 = pMesh->add_vertex(Point3D(center.x() - halfLength, center.y() + halfHeight, center.z() + halfWidth));
	auto v5 = pMesh->add_vertex(Point3D(center.x() - halfLength, center.y() + halfHeight, center.z() - halfWidth));
	auto v6 = pMesh->add_vertex(Point3D(center.x() + halfLength, center.y() + halfHeight, center.z() - halfWidth));
	auto v7 = pMesh->add_vertex(Point3D(center.x() + halfLength, center.y() + halfHeight, center.z() + halfWidth));

	pMesh->add_face(v0, v1, v2); 
	pMesh->add_face(v0, v2, v3);
	pMesh->add_face(v1, v5, v6); 
	pMesh->add_face(v1, v6, v2);
	pMesh->add_face(v5, v4, v7);  
	pMesh->add_face(v5, v7, v6);
	pMesh->add_face(v4, v0, v3);
	pMesh->add_face(v4, v3, v7);
	pMesh->add_face(v3, v2, v6);
	pMesh->add_face(v3, v6, v7);
	pMesh->add_face(v0, v4, v5);
	pMesh->add_face(v0, v5, v1);

	return pMesh;
}