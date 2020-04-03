#pragma once
#include "ECSConfig.h"

namespace Reality
{
	class InputEventSystem : public ECSSystem
	{
	public:
		InputEventSystem();
		void Update(float deltaTime);
	private:
		double mouseX;
		double mouseY;
		bool firstMouse = true;
	};
}

