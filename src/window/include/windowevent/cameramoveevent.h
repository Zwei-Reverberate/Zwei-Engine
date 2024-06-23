#ifndef CAMERAMOVEEVENT_H
#define CAMERAMOVEEVENT_H
#include <include/event/zwevent.h>
#include <string>

const std::string CAMERA_MOVE_EVENT_NAME = CAMERA_MOVE_EVENT_NAME;

class CameraMoveEvent : public Event
{
public:
	CameraMoveEvent(float xoffset, float yoffset);
	std::string getName() const override { return CAMERA_MOVE_EVENT_NAME; }

	float getXoffset() const { return m_xoffset; }
	float getYoffset() const { return m_yoffset; }

private:
	float m_xoffset{.0};
	float m_yoffset{.0};
};

class CameraMoveListener : public EventListener
{
public:
	void onEvent(const Event& event) override;
};


#endif // !CAMERAMOVEEVENT_H
