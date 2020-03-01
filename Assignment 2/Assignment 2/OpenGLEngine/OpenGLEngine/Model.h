#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Camera.h"

using namespace std;

class AssetLoader;
//unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);
namespace Reality
{
	class Model
	{
	public:
		/*  Model Data */
		vector<Material*> materials;
		vector<Mesh> meshes;
		string path;
		string directory;
		bool gammaCorrection;
		int verts;

		/*  Functions   */
		Model();
		void Init();
		inline bool GetDirty(){ return dirty; }
		void Draw();
	private:
		bool dirty = true;
	};
}