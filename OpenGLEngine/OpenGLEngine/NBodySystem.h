#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"
#include "NBodyComponent.h"


namespace Reality
{
	class NBodySystem : public ECSSystem
	{
	public:
		NBodySystem();
		void Update(float deltaTime);

	private :
		float G = 0.3f;
	};
}
