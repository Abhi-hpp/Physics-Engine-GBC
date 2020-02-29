#pragma once
#include "ECSConfig.h"
//#include "PlayerSpawnComponent.h"


namespace Reality
{
	class PlayerSpawnSystem : public ECSSystem
	{
	public:
		PlayerSpawnSystem();
		void Update(float deltaTime);

		void setPlayerEntity(ECSEntity entity)
		{
			player = entity;
		}
		void createPlayer(Vector3 spawnLocation);
	private:
		ECSEntity player;

		int lowerX = -10;
		int upperX = 10;

		int lowerZ = -5;
		int upperZ = 10;

		int height = 17;
	};
}
