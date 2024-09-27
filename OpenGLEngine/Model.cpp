#include "Model.h"
#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

namespace Reality
{
	Model::Model()
	{
		dirty = true;
	}
	// draws the model, and thus all its meshes
	void Model::Draw()
	{
		Init();
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			meshes[i].Draw();
		}
	}

	void Model::Init()
	{
		if (dirty)
		{
			for (unsigned int i = 0; i < materials.size(); i++)
			{
				for (unsigned int j = 0; j < materials[i]->diffuseTextures.size(); j++)
				{
					materials[i]->diffuseTextures[j]->Init();
				}
				for (unsigned int j = 0; j < materials[i]->specularMaps.size(); j++)
				{
					materials[i]->specularMaps[j]->Init();
				}
				materials[i]->Init();
			}
			for (unsigned int i = 0; i < meshes.size(); i++)
			{
				meshes[i].Init();
			}
			dirty = false;
		}
	}
}
