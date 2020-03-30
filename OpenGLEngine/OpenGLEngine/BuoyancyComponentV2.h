#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponentV2
	{
		BuoyancyComponentV2(ECSEntity _attachedEntity = ECSEntity(), float _maxDepth = 5.0f, float _volume = 10.0f, Vector3 _localOffset = Vector3(0.0f, 0.0f, 0.0f))
			: attachedEntity(_attachedEntity), maxDepth(_maxDepth), volume(_volume), localOffset(_localOffset)
		{

		}
		ECSEntity attachedEntity;
		float maxDepth;
		float volume;
		Vector3 localOffset;
	};
}
