#pragma once
#include "ECSConfig.h"
namespace Reality
{
	struct TransformComponent
	{
		TransformComponent(Vector3 _position = Vector3(0, 0, 0), Vector3 _scale = Vector3(1,1,1), Vector3 _eulerAngles = Vector3(0,0,0)) :
			position(_position), scale(_scale), eulerAngles(_eulerAngles)
		{

		}
		Vector3 position;
		Vector3 scale;
		Vector3 eulerAngles;

		inline const Vector3& Right()
		{
			Vector3 radAngle = Vector3(glm::radians(eulerAngles.x),
				glm::radians(eulerAngles.y), glm::radians(eulerAngles.z));
			return glm::quat(radAngle) * Vector3(1, 0, 0);
		}

		inline const Vector3& Up()
		{
			Vector3 radAngle = Vector3(glm::radians(eulerAngles.x),
				glm::radians(eulerAngles.y), glm::radians(eulerAngles.z));
			return glm::quat(radAngle) * Vector3(0, 1, 0);
		}

		inline const Vector3& Forward()
		{
			Vector3 radAngle = Vector3(glm::radians(eulerAngles.x),
				glm::radians(eulerAngles.y), glm::radians(eulerAngles.z));
			return glm::quat(radAngle) * Vector3(0, 0, 1);
		}
	};
}