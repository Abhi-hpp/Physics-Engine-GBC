#pragma once
#include "ECSConfig.h"
#include "TransformComponentV2.h"
#include "MeshComponent.h"
<<<<<<< Updated upstream
=======

class Shader;
class Camera;

>>>>>>> Stashed changes
namespace Reality
{
	class RenderingSystemV2 : public ECSSystem
	{
	public:
		RenderingSystemV2();
		void Update(float deltaTime);
<<<<<<< Updated upstream
=======
	private:
		unsigned int drawMode = 0;
		unsigned int drawModes[2] = { GL_FILL, GL_LINE };
		bool drawModeChanged = false;
>>>>>>> Stashed changes
	};
}
