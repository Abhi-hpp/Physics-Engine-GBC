#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BungeeChordComponent
	{
		BungeeChordComponent(Vector3 _otherTransform = Vector3(0, 0, 0), float _springConstant = 10.0f, float _restLength = 10.0f)
			: springConstant(_springConstant), restLength(_restLength), otherTransform(_otherTransform)
		{

		}

		Vector3 otherTransform;
		float springConstant;
		float restLength;
	};
}
