#include <include/windowevent/camerarotateevent.h>
#include <include/camera/zwcamera.h>


CameraRotateEvent::CameraRotateEvent(float yaw, float pitch) : m_yaw(yaw), m_pitch(pitch){}


void CameraRotateListener::onEvent(const Event& event)
{
	if (event.getName() == CAMERA_ROTATE_EVENT_NAME)
	{
		const CameraRotateEvent& rotateEvent = static_cast<const CameraRotateEvent&>(event);
		ZwCamera* pDefaultCamera = ZwCamera::getDefaultCamera();
		if (!pDefaultCamera)
			return;
		pDefaultCamera->rotate(rotateEvent.getYaw(), rotateEvent.getPitch());
	}
}