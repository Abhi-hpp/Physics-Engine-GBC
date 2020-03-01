#include "RotateSystemV2.h"
#include <glm/gtx/quaternion.hpp>

namespace Reality
{
	RotateSystemV2::RotateSystemV2()
	{
		requireComponent<TransformComponentV2>();
		requireComponent<RotateComponentV2>();
	}

	void RotateSystemV2::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponentV2>();
			auto& rotate = e.getComponent<RotateComponentV2>();

			Vector3 axis = glm::normalize(rotate.rotationVelocity);
			float angle = glm::radians(glm::length(rotate.rotationVelocity)) * deltaTime;
			Quaternion deltaQuat = glm::angleAxis(angle, axis);
			Quaternion quat = glm::normalize(deltaQuat * transform.GetEulerAngles());
			transform.SetOrientation(deltaQuat * transform.GetOrientation());
		}
	}
}
