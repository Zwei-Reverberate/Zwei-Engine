#include <include/renderobject/zwtoolid.h>


ZwToolId::ZwToolId(int id)
{
	m_toolId = id;
}

void ZwToolId::operator=(const ZwToolId& id)
{
	m_toolId = id.m_toolId;
}
