#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct WindThrusterComponent
	{
		WindThrusterComponent(ECSEntity _attachedEntity = ECSEntity(), Vector3 _windDirection = Vector3(0, 0, 1),
			float _wind = 10, Vector3 _sailPosition = Vector3(0,0,0))
			:attachedEntity(_attachedEntity), windDirection(_windDirection), wind(_wind), sailPosition(_sailPosition)
		{

		}

		ECSEntity attachedEntity;
		Vector3 windDirection;
		Vector3 sailPosition;
		float wind;
		float timer = 0;
		
	};
}
