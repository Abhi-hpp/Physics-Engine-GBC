#pragma once
#include "ECSConfig.h"
#include <glm/gtx/quaternion.hpp>

namespace Reality
{
	struct BoxColliderComponent
	{
		BoxColliderComponent(ECSEntity _body = ECSEntity(), Vector3 _size = Vector3(0, 0, 0), Vector3 _offset = Vector3(0, 0, 0), Vector3 _eulerAngles = Vector3(0, 0, 0))
			: body(_body), size(_size), offset(_offset), rp3dId(-1)
		{
			SetRotation(_eulerAngles);
		}
		ECSEntity body;
		Vector3 offset;
		Vector3 size;
		Quaternion orientation;
		// Euler angles in degrees
		inline void SetRotation(Vector3 eulerAngles)
		{
			glm::vec3 rotationInRads = glm::vec3(glm::radians(eulerAngles.x),
				glm::radians(eulerAngles.y), glm::radians(eulerAngles.z));
			orientation = glm::quat(rotationInRads);
		}
		int rp3dId = -1;
	};
}
