#include<include/vulkan/zwsurface.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

void ZwSurface::init(ZwInstance* pInstance, GLFWwindow* pWindow)
{
	if (!pInstance || !pWindow)
		return;

	if (glfwCreateWindowSurface(pInstance->getInstance(), pWindow, nullptr, &m_surface) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create window surface!");
	}
}

void ZwSurface::destroy(ZwInstance* pInstance)
{
	if (!pInstance)
		return;
	vkDestroySurfaceKHR(pInstance->getInstance(), m_surface, nullptr);
}