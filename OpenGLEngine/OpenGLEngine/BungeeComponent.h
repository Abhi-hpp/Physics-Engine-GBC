#pragma once
#include "ECSConfig.h"

/**
* A force generator that applies a spring force only
* when extended.
*/

namespace Reality
{
	struct BungeeComponent
	{
		/** Creates a new bungee with the given parameters. */
		BungeeComponent(float _bungeeConstant = 10.0f,
			float _restLength = 10.0f,
			ECSEntity _connectedEntity = ECSEntity())
			: bungeeConstant(_bungeeConstant),
			restLength(_restLength),
			connectedEntity(_connectedEntity)
			
			
		{

		}
		/** Holds the spring constant. */
		float bungeeConstant;
		/**
		* Holds the length of the bungee at the point it begins to
		* generate a force.
		*/
		float restLength;
		/** The particle at the other end of the spring. */
		ECSEntity connectedEntity;
	};
}
