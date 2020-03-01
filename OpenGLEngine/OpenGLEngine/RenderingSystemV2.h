#pragma once
#include "ECSConfig.h"
#include "TransformComponentV2.h"
#include "MeshComponent.h"

class Shader;
class Camera;

namespace Reality
{
	class RenderingSystemV2 : public ECSSystem
	{
	public:
		RenderingSystemV2();
		void Update(float deltaTime);
	};
}

