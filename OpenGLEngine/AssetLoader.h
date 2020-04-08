#pragma once
#include <unordered_map>
#include <future>
#include <thread>
#include <mutex>
#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Material.h"

namespace Reality 
{
	class RenderUtil;
	class ModelData
	{
	public:
		ModelData(const std::string& _modelPath, const std::vector<std::vector<std::string>>& _textures = { {} })
			:modelPath(_modelPath), textures(_textures){}
		const std::string modelPath;
		const std::vector<std::vector<std::string>> textures;
	};
	class AssetLoader
	{
	public:
		AssetLoader();
		/*Loading*/
		void StartShaderLoading(const std::vector<std::pair<std::string, std::string>>& shaderPaths);
		inline bool ShadersLoaded() { return shadersLoaded.wait_for(std::chrono::seconds(0)) == std::future_status::ready; }
		void StartModelLoading(const std::vector<ModelData>& modelPaths);
		inline bool ModelsLoaded() { return modelsLoaded.valid() && modelsLoaded.wait_for(std::chrono::seconds(0)) == std::future_status::ready; }
		/*Initializing*/
		void InitAssets();
		/*Utils*/
		inline Model* GetModel(int modelId) { std::lock_guard<std::mutex> lock(modelCacheMutex); return modelCache[modelId]; }
		inline bool IsValid(int modelId) { std::lock_guard<std::mutex> lock(modelCacheMutex); return modelId < modelCache.size(); }
		int GetModelId(const std::string& path);	
		/*Set Material Params*/
		void SetLight(glm::vec3 camPos);
	private:
		friend class RenderUtil;
		/*Shader Loading Functions*/
		int LaunchShaderLoadingThreads(const std::vector<std::pair<std::string, std::string>>& shaderPaths);
		void CreateShader(const std::pair<std::string, std::string> &path);

		/*Model Loading Functions*/
		int LaunchModelLoadingThreads(const std::vector<ModelData>& modelPaths);
		void CreateModel(const ModelData &path);
		void LoadDataIntoModel(ModelData const &path, Model* model);
		void processMaterials(const aiScene *scene, Model* model, const std::vector<std::vector<std::string>>& textures = { {} });
		void processNode(aiNode *node, const aiScene *scene, Model* model);
		void processMesh(aiMesh *mesh, const aiScene *scene, Model* model);
		void loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName, Material* material, const string &directory, const std::vector<std::string>& textures = {});

		/*Caches*/
		std::vector<Shader*> shaderCache;
		std::vector<Model*> modelCache;
		std::vector<Texture*> textureCache;
		std::vector<Material*> materialCache;

		/*Threading Vars*/
		std::future<int> shadersLoaded;
		std::future<int> modelsLoaded;
		std::mutex shaderCacheMutex;
		std::mutex modelCacheMutex;
		std::mutex textureCacheMutex;
		std::mutex materialCacheMutex;

		/*One Importer per thread*/
		//std::vector<Assimp::Importer> importer = { Assimp::Importer(), Assimp::Importer(), Assimp::Importer(), Assimp::Importer() };
	};
}

