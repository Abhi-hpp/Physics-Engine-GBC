#pragma once
#include "ECSConfig.h"
#include "TriangleCollisionComponent.h"

namespace Reality
{
	class TriangleCollisionSystem : public ECSSystem
	{
	public:
		TriangleCollisionSystem();
		void Update(float deltaTime);
		void AddBouncyBall(ECSEntity _ball)
		{
			ball = _ball;
		}
		ECSEntity ball;
		bool ballMade = false;
		void GenerateBall();

	};
}
