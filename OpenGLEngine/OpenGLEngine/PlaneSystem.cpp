#include "PlaneSystem.h"
#include "TransformComponent.h"

namespace Reality
{
	PlaneSystem::PlaneSystem()
	{
		requireComponent<PlaneComponent>();
	}

	void PlaneSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			if (e.hasComponent<PlaneComponent>())
			{
				auto& Plane = e.getComponent<PlaneComponent>();

				getWorld().data.renderUtil->DrawTriangle
				(
					Plane.e1.getComponent<TransformComponent>().position,
					Plane.e2.getComponent<TransformComponent>().position,
					Plane.e3.getComponent<TransformComponent>().position,
					Plane.bIsColliding1 ? Color::Red : Color::Green
				);

				getWorld().data.renderUtil->DrawTriangle
				(
					Plane.e1.getComponent<TransformComponent>().position,
					Plane.e3.getComponent<TransformComponent>().position,
					Plane.e4.getComponent<TransformComponent>().position,
					Plane.bIsColliding2 ? Color::Red : Color::Green
				);

				Vector3 trig1_e1Pos = Plane.e1.getComponent<TransformComponent>().position;
				Vector3 trig1_e2Pos = Plane.e2.getComponent<TransformComponent>().position;
				Vector3 trig1_e3Pos = Plane.e3.getComponent<TransformComponent>().position;

				Vector3 trig2_e4Pos = Plane.e4.getComponent<TransformComponent>().position;

				Plane.Center1 = (trig1_e1Pos + trig1_e2Pos + trig1_e3Pos) / 3.0f;
				Plane.Center2 = (trig1_e1Pos + trig1_e3Pos + trig2_e4Pos) / 3.0f;

				Vector3 trig1_v1 = trig1_e1Pos - trig1_e2Pos;
				Vector3 trig1_v2 = trig1_e1Pos - trig1_e3Pos;

				Vector3 trig2_v1 = trig1_e1Pos - trig1_e3Pos;
				Vector3 trig2_v2 = trig1_e1Pos - trig2_e4Pos;


				Plane.normal1 = -glm::normalize(glm::cross(trig1_v1, trig1_v2));
				Plane.normal2 = -glm::normalize(glm::cross(trig2_v1, trig2_v2));


				getWorld().data.renderUtil->DrawLine(
					Plane.Center1,
					Plane.Center1 + Plane.normal1 * 2.0f,
					Color::Blue
				);

				getWorld().data.renderUtil->DrawLine(
					Plane.Center2,
					Plane.Center2 + Plane.normal2 * 2.0f,
					Color::Blue
				);

				//getWorld().data.renderUtil->DrawLine(
				//	Plane.Center2,
				//	Plane.Center2 + Plane.normal2 * 2.0f,
				//	Color::Blue
				//);
			}
		}
	}
}
