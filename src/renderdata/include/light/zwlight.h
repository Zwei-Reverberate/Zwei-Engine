#ifndef ZWLIGHT_H
#define ZWLIGHT_H
#include <glm/glm.hpp>

constexpr int MAX_LIGHT_NUM = 10;

enum class LightType
{
	POINT_LIGHT = 0,
	AMBIENT_LIGHT = 1,
	SPOT_LIGHT = 2
};


class ZwLight
{
public:
	ZwLight() = default;
	ZwLight(const LightType type, const glm::vec3& position = glm::vec3{ 0 },
		float intensity = .0, const glm::vec3& color = glm::vec3{ 0 },
		float cutoff = .0, const glm::vec3& direction = glm::vec3{ 0 }, float outerCutoff = .0);
	
	void setPos(const glm::vec3& position);
	const glm::vec3& getPos() const { return m_position; }

	void setIntensity(const float intensity);
	const float getIntensity() const { return m_intensity; }

	void setColor(const glm::vec3& color);
	const glm::vec3& getColor() const { return m_color; }

	void setCutoff(const float cutoff);
	const float getCutoff() const { return m_cutoff; }

	void setDirection(const glm::vec3& direction);
	const glm::vec3& getDirection() const { return m_direction; }

	void setOuterCutoff(const float outerCutoff);
	const float getOuterCutoff() const { return m_outerCutoff; }

	void setLightType(const LightType type);
	LightType getType() const { return m_type; }


private:
	alignas(16) glm::vec3 m_position{0}; // for point and spot lights
	alignas(4) float m_intensity{ .0 };
	alignas(16) glm::vec3 m_color{ 0};
	alignas(4) float m_cutoff{ .0 }; // for spot lights
	alignas(16) glm::vec3 m_direction{ 0 }; // for directional and spot lights
	alignas(4) float m_outerCutoff{.0}; // for spot lights
	alignas(4) LightType m_type = LightType::POINT_LIGHT; // light type identifier
};


#endif // !ZWLIGHT_H
