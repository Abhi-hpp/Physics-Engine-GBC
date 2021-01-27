#pragma once
#include "ECSConfig.h"
#include "RigidbodyComponent.h"
#include "DragComponent.h"

namespace Reality
{
	class DragSystem : public ECSSystem
	{
	public:
		DragSystem();
		void Update(float deltaTime);
	};
}
