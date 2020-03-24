#pragma once
#include "ECSConfig.h"
#include "TransformComponentV2.h"
#include "AeroSurfaceComponent.h"

namespace Reality
{
	class AeroSurfaceSystem : public ECSSystem
	{
	public:
		AeroSurfaceSystem();
		void Update(float deltaTime);
		Vector3 windVelocity = Vector3(0, 0, 0);
	private:
		const Vector3& CalculateWorldAerodynamicForce(const Mat3& localAeroTensor,
			TransformComponentV2& transform, const Vector3& targetVelocity);
	};
}
