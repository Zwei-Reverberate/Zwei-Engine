#ifndef CAMERAZOOMEVENT_H
#define CAMERAZOOMEVENT_H
#include <include/event/zwevent.h>
#include <string>

const std::string CAMERA_ZOOM_EVENT_NAME = "CameraZoomEvent";

class CameraZoomEvent : public Event
{
public:
	CameraZoomEvent(float yoffset);
	
	float getYoffset() const { return m_yoffset; }
	std::string getName() const override { return CAMERA_ZOOM_EVENT_NAME; }

private:
	float m_yoffset{ .0 };
};

class CameraZoomListener : public EventListener
{
public:
	void onEvent(const Event& event) override;
};


#endif // !CAMERAZOOMEVENT_H
