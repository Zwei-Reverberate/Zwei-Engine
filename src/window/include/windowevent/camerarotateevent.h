#ifndef CAMERAROTATEEVENT_H
#define CAMERAROTATEEVENT_H
#include <include/event/zwevent.h>
#include <string>

const std::string CAMERA_ROTATE_EVENT_NAME = "CameraRotateEvent";

class CameraRotateEvent : public Event
{
public:
	CameraRotateEvent(float yaw, float pitch);
	std::string getName() const override { return CAMERA_ROTATE_EVENT_NAME; }

	float getYaw() const { return m_yaw; }
	float getPitch() const { return m_pitch; }

private:
	float m_yaw;
	float m_pitch;
};

class CameraRotateListener : public EventListener
{
public:
	void onEvent(const Event& event) override;
};


#endif // !CAMERAROTATEEVENT_H
