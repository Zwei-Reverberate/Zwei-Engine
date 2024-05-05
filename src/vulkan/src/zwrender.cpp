#include <include/vulkan/zwrender.h>
#include <include/vulkan/zwinstance.h>
#include <include/vulkan/zwvalidation.h>
#include <include/vulkan/vulkanconst.h>
#include <include/vulkan/zwphysicaldevice.h>
#include <include/vulkan/zwlogicaldevice.h>
#include <include/vulkan/zwsurface.h>
#include <include/vulkan/zwswapchain.h>

void ZwRender::init(GLFWwindow* pWindow)
{
	if (!pWindow)
		return;

	m_pZwInstance = new ZwInstance();
	m_pZwInstance->init();

	m_pSurface = new ZwSurface();
	m_pSurface->init(m_pZwInstance, pWindow);

	if (ENABLEVALIDATIONLAYERS)
	{
		m_pValidation = new ZwValidation();
		m_pValidation->init(m_pZwInstance);
	}

	m_pPhysicalDevice = new ZwPhysicalDevice();
	m_pPhysicalDevice->init(m_pZwInstance, m_pSurface);

	m_pLogicalDevice = new ZwLogicalDevice();
	m_pLogicalDevice->init(m_pPhysicalDevice, m_pSurface);

	m_pSwapChain = new ZwSwapChain();
	m_pSwapChain->init(pWindow, m_pPhysicalDevice, m_pSurface, m_pLogicalDevice);
}

void ZwRender::destroy()
{
	if (!m_pZwInstance || !m_pLogicalDevice || !m_pSurface || !m_pSwapChain)
		return;

	m_pSwapChain->destroy(m_pLogicalDevice);
	m_pLogicalDevice->destroy();
	m_pSurface->destroy(m_pZwInstance);
	
	if (ENABLEVALIDATIONLAYERS && m_pValidation)
		m_pValidation->destroy(m_pZwInstance);
	m_pZwInstance->destroy();

}
