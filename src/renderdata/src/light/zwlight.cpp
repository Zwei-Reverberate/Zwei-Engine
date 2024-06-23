#include <include/light/zwlight.h>
#include <include/math/zwoperationutils.h>


ZwLight::ZwLight(const LightType type, const glm::vec3& position,
	float intensity, const glm::vec3& color,
	float cutoff, const glm::vec3& direction, float outerCutoff):
	m_type(type), m_position(position), m_intensity(intensity), m_color(color), m_cutoff(cutoff), m_direction(direction),m_outerCutoff(outerCutoff){}

void ZwLight::setPos(const glm::vec3& position)
{
	if (position == m_position)
		return;
	m_position = position;
}


void ZwLight::setIntensity(float intensity)
{
	if (ZwOperationUtils::isEqual(intensity, m_intensity))
		return;
	m_intensity = intensity;
}

void ZwLight::setColor(const glm::vec3& color)
{
	if (m_color == color)
		return;
	m_color = color;
}

void ZwLight::setCutoff(const float cutoff)
{
	if (ZwOperationUtils::isEqual(cutoff, m_cutoff))
		return;
	m_cutoff = cutoff;
}


void ZwLight::setDirection(const glm::vec3& direction)
{
	if (direction == m_direction)
		return;
	m_direction = direction;
}

void ZwLight::setOuterCutoff(const float outerCutoff)
{
	if (ZwOperationUtils::isEqual(outerCutoff, m_outerCutoff))
		return;
	m_outerCutoff = outerCutoff;
}

void ZwLight::setLightType(const LightType type)
{
	if (type == m_type)
		return;
	m_type = type;
}