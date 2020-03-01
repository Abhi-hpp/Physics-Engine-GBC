#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "RenderUtil.h"
#include "AssetLoader.h"
#include <memory>
class WorldData
{
public:
	std::unique_ptr<Reality::RenderUtil> renderUtil;
	std::shared_ptr<Reality::AssetLoader> assetLoader;

	void InitRendering()
	{
		assetLoader = std::make_shared<Reality::AssetLoader>();
		renderUtil = std::make_unique<Reality::RenderUtil>(assetLoader);
	}
};
