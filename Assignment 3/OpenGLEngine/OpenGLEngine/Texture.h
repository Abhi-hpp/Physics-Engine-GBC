#pragma once
#include <string>
namespace Reality
{
	class Texture
	{
	public:
		void Init(bool gamma = false);
		Texture(const std::string& _path);
		inline unsigned int GetId() { return textureID; }
		std::string type;
		std::string path;
		inline bool WasLoadedSuccessfully() { return !dirty && loaded; }
	private:
		unsigned int textureID;
		int width, height, nrComponents;
		unsigned char* data;
		bool dirty;
		bool loaded = false;
	};
}

