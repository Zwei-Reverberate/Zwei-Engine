#ifndef ZWINSTANCE_H
#define ZWINSTANCE_H

#include <vulkan/vulkan.h>
class ZwInstance
{
public:
	void init();
	void destroy();
	const VkInstance& getInstance() const { return m_instance; }

private:
	VkInstance m_instance = nullptr;
};

#endif // !ZWINSTANCE_H
