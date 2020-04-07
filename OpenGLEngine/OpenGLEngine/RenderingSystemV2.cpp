#include "RenderingSystemV2.h"
<<<<<<< Updated upstream
=======
#include "Shader.h"
#include "Camera.h"
#include <glm/gtx/euler_angles.hpp> 
>>>>>>> Stashed changes

namespace Reality
{
	RenderingSystemV2::RenderingSystemV2()
	{
		requireComponent<TransformComponentV2>();
		requireComponent<ModelComponent>();
	}

	void RenderingSystemV2::Update(float deltaTime)
	{
<<<<<<< Updated upstream
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponentV2>();
			auto &model = e.getComponent<ModelComponent>();
=======
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
>>>>>>> Stashed changes

			if (getWorld().data.assetLoader->ModelsLoaded())
			{
				getWorld().data.assetLoader->SetLight(getWorld().data.renderUtil->camera.Position);
			}
<<<<<<< Updated upstream
			if (model.modelId < 0)
			{
				model.modelId = getWorld().data.assetLoader->GetModelId(model.mesh);
			}
			if (model.modelId >= 0)
			{
				//Mat4 modelMat = glm::translate(glm::mat4(1.0f), model.offset.x * transform.Right() + model.offset.y * transform.Up() + model.offset.z * transform.Forward()) * transform.transformationMatrix;
				//Mat4 modelMat = glm::translate(transform.transformationMatrix, model.offset.x * transform.Right() + model.offset.y * transform.Up() + model.offset.z * transform.Forward());
				glm::vec3 rotationOffsetInRads = glm::vec3(glm::radians(model.rotation.x), glm::radians(model.rotation.y), glm::radians(model.rotation.z));
				glm::mat4 rotationOffsetMat = glm::toMat4(glm::quat(rotationOffsetInRads));
				Mat4 modelMat = transform.GetTransformationMatrix() * glm::translate(glm::mat4(1.0f), model.offset) * rotationOffsetMat;
				getWorld().data.renderUtil->DrawModel(model.modelId, modelMat);
			}
			getWorld().data.renderUtil->DrawLine(transform.GetPosition(), transform.GetPosition() + transform.Right() * 10.0f, Color::Red);
			getWorld().data.renderUtil->DrawLine(transform.GetPosition(), transform.GetPosition() + transform.Up() * 10.0f, Color::Green);
			getWorld().data.renderUtil->DrawLine(transform.GetPosition(), transform.GetPosition() + transform.Forward() * 10.0f, Color::Blue);
=======
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
>>>>>>> Stashed changes
		}
	}
}
