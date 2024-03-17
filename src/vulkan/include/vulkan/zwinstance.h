#ifndef ZWINSTANCE_H
#define ZWINSTANCE_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class ZwValidation;
class ZwInstance
{
public:
	void init();
	void destroy();
	const VkInstance* getInstanceConst() const { return m_pInstance; }

private:
	VkInstance* m_pInstance = nullptr;
};

#endif // !ZWINSTANCE_H
