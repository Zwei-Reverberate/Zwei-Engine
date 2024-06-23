#ifndef ZWUNIFORM_H
#define ZWUNIFORM_H
#include <include/renderdata/zwtrans.h>
#include <include/light/zwlight.h>
#include <vector>

class ZwUniform
{
public:
	ZwUniform() = default;
	ZwUniform(const ZwTrans& trans, const std::vector<ZwLight>& lights);

	const ZwTrans& getTrans() const { return m_trans; }
	void setTrans(const ZwTrans& trans);

	const ZwLight* getLights() const { return m_lights; }
	void setLights(const std::vector<ZwLight>& lights);
	int getLightNum() const { return m_lightNum; }

	const glm::vec3& getViewPos() const { return m_viewPos; }
	void setViewPos(const glm::vec3& viewPos);

private:
	alignas(16) ZwTrans m_trans;
	alignas(16) ZwLight m_lights[MAX_LIGHT_NUM];
	alignas(16) glm::vec3 m_viewPos{ 0 };
	alignas(4) int m_lightNum{1};
};

#endif // !ZWUNIFORM_H
