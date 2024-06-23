#ifndef ZWTRANS_H
#define ZWTRANS_H
#include <glm/glm.hpp>

class ZwTrans
{
public:
	ZwTrans() = default;
	ZwTrans(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj);

	const glm::mat4& getModelMat() const { return m_model; }
	const glm::mat4& getViewMat() const { return m_view; }
	const glm::mat4& getPorjMat() const { return m_proj; }

	void setModelMat(const glm::mat4& model);
	void setViewMat(const glm::mat4& view);
	void setProjMat(const glm::mat4& proj);


private:
	alignas(16) glm::mat4 m_model{ 1 };
	alignas(16) glm::mat4 m_view{ 1 };
	alignas(16) glm::mat4 m_proj{ 1 };
};


#endif // !ZWTRANS_H
