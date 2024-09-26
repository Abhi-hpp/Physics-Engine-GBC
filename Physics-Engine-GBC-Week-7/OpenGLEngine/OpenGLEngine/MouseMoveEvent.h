#pragma once
#include "ECSConfig.h"
namespace Reality
{
	struct MouseMoveEvent
	{
		MouseMoveEvent(float _x = 0, float _y = 0, float _deltaX = 0, float _deltaY = 0)
			: x(_x), y(_y), deltaX(_deltaX), deltaY(_deltaY){}
		float x;
		float y;
		float deltaX;
		float deltaY;
	};
}