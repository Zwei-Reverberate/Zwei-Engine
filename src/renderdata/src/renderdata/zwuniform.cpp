#include <include/renderdata/zwuniform.h>


void ZwUniform::setTrans(const ZwTrans& trans)
{
	m_trans = trans;
}

ZwUniform:: ZwUniform(const ZwTrans& trans, const std::vector<ZwLight>& lights):m_trans(trans)
{
}

void ZwUniform::setLights(const std::vector<ZwLight>& lights)
{
	if (lights.empty() || lights.size() > MAX_LIGHT_NUM)
		return;
	
	m_lightNum = lights.size();
	for (int i = 0; i < lights.size(); ++i)
	{
		m_lights[i] = lights[i];
	}
}


void ZwUniform::setViewPos(const glm::vec3& viewPos)
{
	if (m_viewPos == viewPos)
		return;
	m_viewPos = viewPos;
}