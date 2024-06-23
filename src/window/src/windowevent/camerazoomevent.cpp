#include <include/windowevent/camerazoomevent.h>
#include <include/camera/zwcamera.h>

CameraZoomEvent::CameraZoomEvent(float yoffset):m_yoffset(yoffset)
{
}

void CameraZoomListener::onEvent(const Event& event)
{
	if (event.getName() == CAMERA_ZOOM_EVENT_NAME)
	{
		const CameraZoomEvent& zoomEvent = static_cast<const CameraZoomEvent&>(event);
		ZwCamera* pDefaultCamera = ZwCamera::getDefaultCamera();
		if (!pDefaultCamera)
			return;
		pDefaultCamera->zoom(zoomEvent.getYoffset());
	}
}
