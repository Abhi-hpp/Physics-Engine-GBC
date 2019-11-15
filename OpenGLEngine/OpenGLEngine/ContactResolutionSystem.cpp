#include "ContactResolutionSystem.h"
#include "TransformComponentV2.h"
#include <string>

namespace Reality
{

	ContactResolutionSystem::ContactResolutionSystem(rp3d::CollisionWorld& _rp3dWorld) : rp3dWorld(_rp3dWorld)
	{
	}

	void ContactResolutionSystem::Update(float deltaTime)
	{
		auto contactEvents = getWorld().getEventManager().getEvents<ContactEvent>();
		for (auto contact : contactEvents)
		{
			getWorld().data.renderUtil->DrawSphere(contact.worldPoint1, 0.4f, Color::Red);
			getWorld().data.renderUtil->DrawSphere(contact.worldPoint2, 0.4f, Color::Blue);
			getWorld().data.renderUtil->DrawLine(contact.worldPoint1, contact.worldPoint2, Color::Beige);
			
		}
		getWorld().data.renderUtil->RenderText("Num Contacts = " + to_string(contactEvents.size()), 1920 * 0.5f - 100, 1080 * 0.5f, 0.5f, Color::Red);
	}
}
