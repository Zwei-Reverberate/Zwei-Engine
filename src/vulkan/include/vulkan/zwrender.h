#ifndef ZWRENDER_H
#define	ZWRENDER_H
#include <include/vulkan/zwinstance.h>

class ZwValidation;
class ZwPhysicalDevice;
class ZwLogicalDevice;
class ZwSurface;
class ZwSwapChain;
class ZwRender
{
public:
	void init(GLFWwindow* pWindow);
	void destroy();

private:
	ZwInstance* m_pZwInstance = nullptr;
	ZwValidation* m_pValidation = nullptr; 
	ZwPhysicalDevice* m_pPhysicalDevice = nullptr;
	ZwLogicalDevice* m_pLogicalDevice = nullptr;
	ZwSurface* m_pSurface = nullptr;
	ZwSwapChain* m_pSwapChain = nullptr;
};

#endif // !ZWRENDER_H
