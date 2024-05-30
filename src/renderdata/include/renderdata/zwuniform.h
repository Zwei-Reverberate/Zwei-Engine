#ifndef ZWUNIFORM_H
#define ZWUNIFORM_H
#include <glm/glm.hpp>

class ZwUniform
{
public:
	ZwUniform() = default;
	ZwUniform(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj);
	
	const glm::mat4& getModelMat() const { return m_model; }
	const glm::mat4& getViewMat() const { return m_view; }
	const glm::mat4& getPorjMat() const { return m_proj; }

	void setModelMat(const glm::mat4& model);
	void setViewMat(const glm::mat4& view);
	void setProjMat(const glm::mat4& proj);

private:
	glm::mat4 m_model{ 1 };
	glm::mat4 m_view{ 1 };
	glm::mat4 m_proj{ 1 };
};


#endif // !ZWUNIFORM_H
