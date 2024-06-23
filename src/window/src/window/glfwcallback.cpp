#include <include/window/glfwcallback.h>
#include <include/windowevent/camerarotateevent.h>
#include <include/windowevent/camerazoomevent.h>
#include <include/windowevent/cameramoveevent.h>

namespace GlfwCallback
{
    bool rightMouseButtonPressed = false;
    bool middleMouseButtonPressed = false;
    float lastX = 400, lastY = 300;
    float yaw = -90.0f, pitch = 0.0f;
};

void GlfwCallback::mouseButtonCallback(GLFWwindow* pWindow, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) 
    {
        rightMouseButtonPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) 
    {
        rightMouseButtonPressed = false;
    }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) 
    {
        middleMouseButtonPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE) 
    {
        middleMouseButtonPressed = false;
    }
}


void GlfwCallback::cursorPositionCallback(GLFWwindow* pWindow, double xpos, double ypos)
{
    if (rightMouseButtonPressed) 
    {
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        CameraRotateEvent cameraRotateEvent(yaw, pitch);
        EventManager* pEventManager = EventManager::getEventManager();
        if (!pEventManager)
            return;
        pEventManager->sendEvent(cameraRotateEvent);
    }
    else if (middleMouseButtonPressed)
    {
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.0048f; // Adjust sensitivity as needed
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        CameraMoveEvent cameraMoveEvent(xoffset, yoffset);
        EventManager* pEventManager = EventManager::getEventManager();
        if (!pEventManager)
            return;
        pEventManager->sendEvent(cameraMoveEvent);
    }
    else 
    {
        lastX = xpos;
        lastY = ypos;
    }
}

void GlfwCallback::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    CameraZoomEvent cameraZoomEvent(yoffset);
    EventManager* pEventManager = EventManager::getEventManager();
    if (!pEventManager)
        return;
    pEventManager->sendEvent(cameraZoomEvent);
}