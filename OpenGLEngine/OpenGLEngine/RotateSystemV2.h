#pragma once
#include "ECSConfig.h"
#include "TransformComponentV2.h"
#include "RotateComponentV2.h"

namespace Reality
{
	class RotateSystemV2 : public ECSSystem
	{
	public:
		RotateSystemV2();
		void Update(float deltaTime);
	private:
		float timer = 0;
	};
}
