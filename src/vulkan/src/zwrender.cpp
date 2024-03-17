#include <include/vulkan/zwrender.h>
#include <include/vulkan/zwinstance.h>
#include <include/vulkan/zwvalidation.h>
#include <include/vulkan/vulkanconst.h>

void ZwRender::init()
{
	m_pZwInstance = new ZwInstance();
	m_pZwInstance->init();

	if (ENABLEVALIDATIONLAYERS)
	{
		m_pValidation = new ZwValidation();
		m_pValidation->init(m_pZwInstance);
	}
}

void ZwRender::destroy()
{
	if (!m_pZwInstance)
		return;
	
	if (ENABLEVALIDATIONLAYERS && m_pValidation)
		m_pValidation->destroy(m_pZwInstance);

	m_pZwInstance->destroy();
}
