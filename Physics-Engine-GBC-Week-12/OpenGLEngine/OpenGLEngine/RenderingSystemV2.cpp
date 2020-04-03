#include "RenderingSystemV2.h"
#include "Shader.h"
#include "Camera.h"
#include <glm/gtx/euler_angles.hpp> 

namespace Reality
{
	RenderingSystemV2::RenderingSystemV2()
	{
		requireComponent<TransformComponentV2>();
		requireComponent<ModelComponent>();
	}

	void RenderingSystemV2::Update(float deltaTime)
	{
		if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_F1) == GLFW_PRESS && !drawModeChanged)
		{
			drawMode++;
			drawMode = drawMode % 2;
			drawModeChanged = true;
		}
		else if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_F1) == GLFW_RELEASE)
		{
			drawModeChanged = false;
		}
		for (auto e : getEntities())
		{
			auto &transform = e.getComponent<TransformComponentV2>();
			auto &mesh = e.getComponent<ModelComponent>();

			if (getWorld().data.assetLoader->ModelsLoaded())
			{
				getWorld().data.assetLoader->SetLight(getWorld().data.renderUtil->camera.Position);
			}
			if (mesh.modelId < 0)
			{
				mesh.modelId = getWorld().data.assetLoader->GetModelId(mesh.mesh);
			}
			if (mesh.modelId >= 0)
			{
				getWorld().data.renderUtil->DrawModel(mesh.modelId, transform.GetTransformationMatrix() * mesh.GetModelOffsetTransformation(), drawModes[drawMode]);
			}

			if (DEBUG_LOG_LEVEL > 0)
			{
				// X
				getWorld().data.renderUtil->DrawLine(transform.GetPosition(),
					transform.GetPosition() + transform.Right() * 10.0f, Color::Red);
				// Y
				getWorld().data.renderUtil->DrawLine(transform.GetPosition(),
					transform.GetPosition() + transform.Up() * 10.0f, Color::Green);
				// Z
				getWorld().data.renderUtil->DrawLine(transform.GetPosition(),
					transform.GetPosition() + transform.Forward() * 10.0f, Color::Blue);
			}
		}
	}
}
