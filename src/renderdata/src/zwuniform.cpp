#include <include/renderdata/zwuniform.h>

ZwUniform::ZwUniform(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj):m_model(model), m_view(view), m_proj(proj)
{}


void ZwUniform::setModelMat(const glm::mat4& model)
{
	if (model == m_model)
		return;
	m_model = model;
}
void ZwUniform::setViewMat(const glm::mat4& view)
{
	if (view == m_view)
		return;
	m_view = view;
}
void ZwUniform::setProjMat(const glm::mat4& proj)
{
	if (proj == m_proj)
		return;
	m_proj = proj;
}