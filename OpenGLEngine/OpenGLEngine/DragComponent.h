#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct DragComponent
	{
		DragComponent(float _linearDrag = 0.3f, float _angularDrag = 0.3f)
			:linearDrag(_linearDrag), angularDrag(_angularDrag)
		{

		}
		float linearDrag;
		float angularDrag;
	};
}
