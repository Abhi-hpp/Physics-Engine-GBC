#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct DragComponent
	{
		DragComponent(float _linearDrag = 0.7f, float _angularDrag = 0.7f)
			:linearDrag(_linearDrag), angularDrag(_angularDrag)
		{

		}
		float linearDrag;
		float angularDrag;
	};
}
