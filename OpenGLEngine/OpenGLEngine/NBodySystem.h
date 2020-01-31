#pragma once
#include "ECSConfig.h"
#include "NBodyComponent.h"


namespace Reality
{
	class NBodySystem : public ECSSystem
	{
	public:
		NBodySystem();
		void Update(float deltaTime);

		float gravConstant = 1000.0f;
	};
}
