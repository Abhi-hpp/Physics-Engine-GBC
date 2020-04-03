#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(ECSEntity _targetEntity = ECSEntity(), 
			float _density = 0.0f, Vector3 _localOffset = Vector3(0, 0, 0),
			float _maxDepth = 0.0f, Vector3 _volume = Vector3(0, 0, 0))
			:targetEntity(_targetEntity),
			density(_density),
			localOffset(_localOffset),
			volume(_volume),
			maxDepth(_maxDepth)
		{

		}
		ECSEntity targetEntity;
		float density;
		Vector3 localOffset;
		Vector3 volume;
		float maxDepth;
	};
}