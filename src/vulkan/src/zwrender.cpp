#include <include/vulkan/zwrender.h>
#include <include/vulkan/zwinstance.h>
#include <include/vulkan/zwvalidation.h>
#include <include/vulkan/vulkanconst.h>
#include <include/vulkan/zwphysicaldevice.h>
#include <include/vulkan/zwlogicaldevice.h>

void ZwRender::init()
{
	m_pZwInstance = new ZwInstance();
	m_pZwInstance->init();

	if (ENABLEVALIDATIONLAYERS)
	{
		m_pValidation = new ZwValidation();
		m_pValidation->init(m_pZwInstance);
	}

	m_pPhysicalDevice = new ZwPhysicalDevice();
	m_pPhysicalDevice->init(m_pZwInstance);

	m_pLogicalDevice = new ZwLogicalDevice();
	m_pLogicalDevice->init(m_pPhysicalDevice);
}

void ZwRender::destroy()
{
	if (!m_pZwInstance || !m_pLogicalDevice)
		return;

	m_pLogicalDevice->destroy();
	
	if (ENABLEVALIDATIONLAYERS && m_pValidation)
		m_pValidation->destroy(m_pZwInstance);
	m_pZwInstance->destroy();

}
