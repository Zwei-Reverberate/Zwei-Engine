#ifndef ZWCAMERA_H
#define	ZWCAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ZwCamera
{
public:
    static ZwCamera* getDefaultCamera()
    {
        static ZwCamera camera(glm::vec3(1.7f, 1.4f, 2.5f), glm::vec3(-0.4f, -0.4f, -0.8f), 45.0f, 1280.0 / 720.0, 0.1f, 100.0f);
        return &camera;
    }

    const glm::mat4& getViewMatrix() const { return m_viewMatrix; }
    const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; }
    const glm::vec3& getPos() const { return m_position; }

    void rotate(float yaw, float pitch);
    void zoom(float yoffset);
    void move(float xoffset, float yoffset);

private:
    void updateViewMatrix();
    void updateProjectionMatrix();

    // 暂时只提供一个默认的全局 camera
    ZwCamera() = default;
    ZwCamera(const glm::vec3& position, const glm::vec3& target, float fov, float aspect, float near, float far);

private:
    glm::vec3 m_position{ 0 };
    glm::vec3 m_target{ 0 };
    float m_fov{ .0 };
    float m_aspect{ .0 };
    float m_near{ .0 };
    float m_far{ .0 };
    glm::mat4 m_viewMatrix{ 1 };
    glm::mat4 m_projectionMatrix{ 1 };
};

#endif // !ZWCAMERA_H
