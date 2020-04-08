#include "CameraLookSystem.h"
#include "MouseMoveEvent.h"

namespace Reality
{
	CameraLookSystem::CameraLookSystem()
	{
		requireComponent<CameraLookComponent>();
	}

	void CameraLookSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			Camera& camera = getWorld().data.renderUtil->camera;
			auto mouseMoveEvents = getWorld().getEventManager().getEvents<MouseMoveEvent>();
			for (auto event : mouseMoveEvents)
			{
				camera.ProcessMouseMovement(event.deltaX, event.deltaY);
			}
		}
	}
}
