#ifndef ZWTOOLID_H
#define ZWTOOLID_H
#include <include/vulkan/vulkanconst.h>

class ZwToolId
{
public:
	ZwToolId() = default;
	ZwToolId(int id);

	bool operator == (const ZwToolId& id) const { return m_toolId == id.m_toolId; }
	bool operator < (const ZwToolId& id) const { return m_toolId < id.m_toolId; }
	void operator = (const ZwToolId& id);
	
private:
	int m_toolId = INVALID_TOOL_ID;
};

#endif // !ZWTOOLID_H
