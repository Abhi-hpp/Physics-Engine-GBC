#include "RenderingSystem.h"
#include "Shader.h"
#include "Camera.h"
#include <glm/gtx/euler_angles.hpp> 

namespace Reality
{
	RenderingSystem::RenderingSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<ModelComponent>();
	}

	void RenderingSystem::Update(float deltaTime)
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
			auto &transform = e.getComponent<TransformComponent>();
			auto &mesh = e.getComponent<ModelComponent>();

			if (getWorld().data.assetLoader->ModelsLoaded())
			{
				getWorld().data.assetLoader->SetLight(getWorld().data.renderUtil->camera.Position);
			}
			if (mesh.modelId < 0)
			{
				mesh.modelId = getWorld().data.assetLoader->GetModelId(mesh.mesh);
			}
			if(mesh.modelId >= 0)
			{ 
				getWorld().data.renderUtil->DrawModel(mesh.modelId, transform.position, transform.scale, transform.eulerAngles, drawModes[drawMode]);
			}

			if (DEBUG_LOG_LEVEL > 0)
			{
				// X
				getWorld().data.renderUtil->DrawLine(transform.position,
					transform.position + transform.Right() * 10.0f, Color::Red);
				// Y
				getWorld().data.renderUtil->DrawLine(transform.position,
					transform.position + transform.Up() * 10.0f, Color::Green);
				// Z
				getWorld().data.renderUtil->DrawLine(transform.position,
					transform.position + transform.Forward() * 10.0f, Color::Blue);
			}
		}
	}
}

