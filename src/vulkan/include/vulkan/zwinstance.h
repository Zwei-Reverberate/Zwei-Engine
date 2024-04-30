#ifndef ZWINSTANCE_H
#define ZWINSTANCE_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class ZwInstance
{
public:
	void init();
	void destroy();
	const VkInstance& getInstanceConst() const { return m_instance; }

private:
	VkInstance m_instance = nullptr;
};

#endif // !ZWINSTANCE_H
