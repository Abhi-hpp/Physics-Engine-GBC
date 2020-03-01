#include "RenderingSystemV2.h"
#include "Shader.h"
#include "Camera.h"

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
			auto transform = e.getComponent<TransformComponentV2>();
			auto& mesh = e.getComponent<ModelComponent>();

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
				getWorld().data.renderUtil->DrawModel(mesh.modelId, transform.GetTransformationMatrix());
			}
		}
	}
}
