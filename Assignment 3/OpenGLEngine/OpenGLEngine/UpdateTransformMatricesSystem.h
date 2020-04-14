#pragma once
#include "ECSConfig.h"
#include "TransformComponentV2.h"

namespace Reality
{
	class UpdateTransformMatricesSystem : public ECSSystem
	{
	public:
		UpdateTransformMatricesSystem();
		void Update(float deltaTime);
	};
}
