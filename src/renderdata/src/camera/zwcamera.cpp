#include <include/camera/zwcamera.h>

const glm::vec3 WORLD_UP{ 0 ,1 , 0 };

ZwCamera::ZwCamera(const glm::vec3& position, const glm::vec3& target, float fov, float aspect, float near, float far) :
	m_position(position), m_target(target), m_fov(fov), m_aspect(aspect), m_near(near), m_far(far)
{
	updateViewMatrix();
	updateProjectionMatrix();
}

void ZwCamera::updateViewMatrix()
{
	m_viewMatrix = glm::lookAt(m_position, m_position + m_target, WORLD_UP);
}


void ZwCamera::updateProjectionMatrix()
{
	m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
	m_projectionMatrix[1][1] *= -1;
}


void ZwCamera::rotate(float yaw, float pitch)
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	m_target = glm::normalize(direction);
	updateViewMatrix();
}

void ZwCamera::zoom(float yoffset)
{
	// m_fov -= yoffset;
	// if (m_fov < 1.0f) 
	//	m_fov = 1.0f;
	// if (m_fov > 45.0f) 
	//	m_fov = 45.0f;
	// updateProjectionMatrix();
	float zoomSpeed = 0.24f; // 调整缩放速度
	glm::vec3 direction = glm::normalize(m_target - m_position);
	m_position += direction * yoffset * zoomSpeed;
	updateViewMatrix();
}


void ZwCamera::move(float xoffset, float yoffset)
{
	glm::vec3 right = glm::normalize(glm::cross(m_target, WORLD_UP));
	glm::vec3 up = glm::normalize(glm::cross(right, m_target));

	m_position += right * xoffset;
	m_position += up * yoffset;

	updateViewMatrix();
}