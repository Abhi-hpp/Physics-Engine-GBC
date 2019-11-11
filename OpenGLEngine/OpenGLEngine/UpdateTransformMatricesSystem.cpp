#include "UpdateTransformMatricesSystem.h"

namespace Reality
{
	UpdateTransformMatricesSystem::UpdateTransformMatricesSystem()
	{
		requireComponent<TransformComponentV2>();
	}

	void UpdateTransformMatricesSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponentV2>();
			//transform.scaleMatrix = glm::scale(glm::mat4(1.0f), transform.scale);
			//transform.translationMatrix = glm::translate(glm::mat4(1.0f), transform.position);
			//transform.rotationMatrix = glm::toMat4(transform.orientation);
			//transform.unScaledTransformationMatrix = transform.translationMatrix * transform.rotationMatrix;
			//transform.transformationMatrix = transform.unScaledTransformationMatrix * transform.scaleMatrix;
		}
	}
}
