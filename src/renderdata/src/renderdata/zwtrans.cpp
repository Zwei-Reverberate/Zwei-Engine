#include <include/renderdata/zwtrans.h>

ZwTrans::ZwTrans(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj) :m_model(model), m_view(view), m_proj(proj)
{}


void ZwTrans::setModelMat(const glm::mat4& model)
{
	if (model == m_model)
		return;
	m_model = model;
}
void ZwTrans::setViewMat(const glm::mat4& view)
{
	if (view == m_view)
		return;
	m_view = view;
}
void ZwTrans::setProjMat(const glm::mat4& proj)
{
	if (proj == m_proj)
		return;
	m_proj = proj;
}
