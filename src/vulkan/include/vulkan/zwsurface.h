#ifndef ZWSURFACE_H
#define ZWSURFACE_H
#include <include/vulkan/zwinstance.h>

class ZwSurface
{
public:
	void init(ZwInstance* pInstance, GLFWwindow* pWindow);
	void destroy(ZwInstance* pInstance);
	const VkSurfaceKHR& getSurfaceConst() const { return m_surface; }

private:
	VkSurfaceKHR m_surface = nullptr;
};

#endif // !ZWSURFACE_H
