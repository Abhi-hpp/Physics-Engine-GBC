#include "AssetLoader.h"


namespace Reality
{
	AssetLoader::AssetLoader()
	{
	}


	int AssetLoader::GetModelId(const std::string& path)
	{
		std::lock_guard<std::mutex> lock(modelCacheMutex);
		for (std::vector<Model>::size_type i = 0; i < modelCache.size(); i++)
		{
			if (modelCache[i]->path == path)
			{
				return i;
			}
		}
		return -1;
	}

	void AssetLoader::StartShaderLoading(const std::vector<std::pair<std::string, std::string>>& shaderPaths)
	{
		shadersLoaded = std::async(std::launch::async, &AssetLoader::LaunchShaderLoadingThreads, this, shaderPaths);
	}

	int AssetLoader::LaunchShaderLoadingThreads(const std::vector<std::pair<std::string, std::string>>& shaderPaths)
	{
		std::vector<std::thread> shaderLoaders;
		for (const std::pair<std::string, std::string>& path : shaderPaths)
		{
			shaderLoaders.emplace_back(&AssetLoader::CreateShader, this, std::ref(path));
		}
		for (int i = 0; i < shaderLoaders.size(); i++)
		{
			shaderLoaders[i].join();
		}
		return 1;
	}

	void AssetLoader::CreateShader(const std::pair<std::string, std::string> &path)
	{
		// Create the shader
		Shader* shader = new Shader(path.first.c_str(), path.second.c_str());
		// Put in cache
		shaderCacheMutex.lock();
		shaderCache.push_back(shader);
		shaderCacheMutex.unlock();
	}

	void AssetLoader::StartModelLoading(const std::vector<ModelData>& modelPaths)
	{
		modelsLoaded = std::async(std::launch::async, &AssetLoader::LaunchModelLoadingThreads, this, modelPaths);
	}

	int AssetLoader::LaunchModelLoadingThreads(const std::vector<ModelData>& modelPaths)
	{
		std::vector<std::thread> modelLoaders;
		for (const ModelData& path : modelPaths)
		{
			modelLoaders.emplace_back(&AssetLoader::CreateModel, this, std::ref(path));
		}
		for (int i = 0; i < modelLoaders.size(); i++)
		{
			modelLoaders[i].join();
		}
		return 1;
	}

	void AssetLoader::CreateModel(const ModelData &path)
	{
		// Create the model
		Model* model = new Model();
		// Use Assimp to load file
		LoadDataIntoModel(path, model);
		// Put in cache
		modelCacheMutex.lock();
		modelCache.push_back(model);
		modelCacheMutex.unlock();
	}

	void AssetLoader::LoadDataIntoModel(ModelData const &path, Model* model)
	{
		// read file via ASSIMP
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path.modelPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		// check for errors
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
			return;
		}
		model->path = path.modelPath;
		// retrieve the directory path of the filepath
		model->directory = path.modelPath.substr(0, path.modelPath.find_last_of('/'));
		// process materials
		processMaterials(scene, model, path.textures);
		// process ASSIMP's root node recursively
		processNode(scene->mRootNode, scene, model);
	}

	void AssetLoader::processMaterials(const aiScene *scene, Model* model, const std::vector<std::vector<std::string>>& textures)
	{
		// process materials
		for (int i = 0; i < scene->mNumMaterials; i++)
		{
			aiMaterial* material = scene->mMaterials[i];

			materialCacheMutex.lock();
			materialCache.push_back(new Material(shaderCache[0]));
			Material* mat = materialCache.back();
			materialCacheMutex.unlock();

			model->materials.push_back(mat);
			// 1. diffuse maps
			if (textures.size() > i)
			{
				loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", mat, model->directory, textures[i]);
			}
			else
			{
				loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", mat, model->directory);
			}
			loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", mat, model->directory);
			// Set properties
			float shininess;
			material->Get(AI_MATKEY_SHININESS, shininess);
			mat->SetShininess(shininess);
		}
	}

	void AssetLoader::processNode(aiNode *node, const aiScene *scene, Model* model)
	{
		// process each mesh located at the current node
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			// the node object only contains indices to index the actual objects in the scene. 
			// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			processMesh(mesh, scene, model);
			model->verts += mesh->mNumVertices;
		}
		// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene, model);
		}
	}

	void AssetLoader::processMesh(aiMesh *mesh, const aiScene *scene, Model* model)
	{
		//// process materials
		//aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		//materialCacheMutex.lock();
		//materialCache.push_back(new Material(shaderCache[0]));
		//Material* mat = materialCache.back();
		//materialCacheMutex.unlock();

		//model->materials.push_back(mat);
		model->meshes.push_back(Mesh(model, mesh->mMaterialIndex, std::string(mesh->mName.C_Str())));
		// Walk through each of the mesh's vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
			// positions
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;
			// normals
			if (mesh->mNormals)
			{
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
			}
			else
			{
				vector = glm::vec3(0, 0, 0);
			}
			vertex.Normal = vector;
			// texture coordinates
			if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			// tangent
			if (mesh->mTangents)
			{
				vector.x = mesh->mTangents[i].x;
				vector.y = mesh->mTangents[i].y;
				vector.z = mesh->mTangents[i].z;
			}
			else
			{
				vector = glm::vec3(0, 0, 0);
			}
			vertex.Tangent = vector;
			// bitangent
			if (mesh->mBitangents)
			{
				vector.x = mesh->mBitangents[i].x;
				vector.y = mesh->mBitangents[i].y;
				vector.z = mesh->mBitangents[i].z;
			}
			else
			{
				vector = glm::vec3(0, 0, 0);
			}
			vertex.Bitangent = vector;
			model->meshes.back().vertices.push_back(vertex);
		}
		// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			// retrieve all indices of the face and store them in the indices vector
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				model->meshes.back().indices.push_back(face.mIndices[j]);
		}
		
		// 1. diffuse maps
		//loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", mat, model->directory);
	}

	void AssetLoader::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName, Material* material, const string &directory, const std::vector<std::string>& textures)
	{
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			string filename = string(str.C_Str());
			if (textures.size() > i)
			{
				filename = textures[i];
			}
			filename = directory + '/' + filename;
			//filename = "Resources/Models/nanosuit/body_dif.png";
			// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
			bool skip = false;
			textureCacheMutex.lock();
			for (unsigned int j = 0; j < textureCache.size(); j++)
			{
				if (std::strcmp(textureCache[j]->path.data(), filename.c_str()) == 0)
				{
					if (typeName == "texture_diffuse")
					{
						material->diffuseTextures.push_back(textureCache[j]);
					}
					else if(typeName == "texture_specular")
					{
						material->specularMaps.push_back(textureCache[j]);
					}
					skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
					break;
				}
			}
			if (!skip)
			{   // if texture hasn't been loaded already, load it
				Texture* texture = new Texture(filename);
				texture->type = typeName;
				textureCache.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
				if (typeName == "texture_diffuse")
				{
					material->diffuseTextures.push_back(textureCache.back());
				}
				else if (typeName == "texture_specular")
				{
					material->specularMaps.push_back(textureCache.back());
				}
			}
			textureCacheMutex.unlock();
		}
	}

	void AssetLoader::InitAssets()
	{
		for (auto texture : textureCache)
		{
			texture->Init();
		}
		for (auto material : materialCache)
		{
			material->Init();
		}
		for (auto model : modelCache)
		{
			for (auto mesh : model->meshes)
			{
				mesh.Init();
			}
		}
	}

	void AssetLoader::SetLight(glm::vec3 camPos)
	{
		for (auto model : modelCache)
		{
			for (auto mat : model->materials)
			{
				// directional light
				mat->use();
				mat->setVec3("viewPos", camPos);
				//mat->setFloat("material.shininess", 32.0f);
			}
		}
	}
}
