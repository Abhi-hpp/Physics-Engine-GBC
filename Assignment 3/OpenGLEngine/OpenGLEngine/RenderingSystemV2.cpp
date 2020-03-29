#include "RenderingSystemV2.h"

namespace Reality
{
	RenderingSystemV2::RenderingSystemV2()
	{
		requireComponent<TransformComponentV2>();
		requireComponent<ModelComponent>();
	}

	void RenderingSystemV2::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponentV2>();
			auto &model = e.getComponent<ModelComponent>();

			if (getWorld().data.assetLoader->ModelsLoaded())
			{
				getWorld().data.assetLoader->SetLight(getWorld().data.renderUtil->camera.Position);
			}
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
		}
	}
}
