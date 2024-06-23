#include <include/windowevent/cameramoveevent.h>
#include <include/camera/zwcamera.h>

CameraMoveEvent::CameraMoveEvent(float xoffset, float yoffset):m_xoffset(xoffset), m_yoffset(yoffset){}




void CameraMoveListener::onEvent(const Event& event)
{
	if (event.getName() == CAMERA_MOVE_EVENT_NAME)
	{
		const CameraMoveEvent& moveEvent = static_cast<const CameraMoveEvent&>(event);
		ZwCamera* pDefaultCamera = ZwCamera::getDefaultCamera();
		if (!pDefaultCamera)
			return;
		pDefaultCamera->move(moveEvent.getXoffset(), moveEvent.getYoffset());
	}
}