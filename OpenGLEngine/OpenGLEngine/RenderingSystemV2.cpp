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
				getWorld().data.renderUtil->DrawModel(mesh.modelId, transform.GetTransformationMatrix());
			}

			// Draw
			//getWorld().data.renderUtil->DrawCube(transform.position, Vector3(10,10,10), transform.eulerAngles);
			//getWorld().data.renderUtil->DrawCube(transform.position + Vector3(0, transform.scale.y , 0) * 7.5f, transform.scale * 15.0f, transform.eulerAngles);
			//getWorld().data.renderUtil->DrawLine(transform.position - Vector3(1, 1, 1), transform.position + Vector3(1, 1, 1));
		}
	}
}
