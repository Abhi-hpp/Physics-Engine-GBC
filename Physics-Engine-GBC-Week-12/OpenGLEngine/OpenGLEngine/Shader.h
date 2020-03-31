#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
namespace Reality
{
	class Shader
	{
	public:
		Shader(const char* vertexPath = "Shaders/vertexDefault.vs", const char* fragmentPath = "Shaders/fragmentDefault.fs", const char* geometryPath = nullptr);
		std::string vertexCode;
		std::string fragmentCode;
		const char* vShaderCode;
		const char* fShaderCode;
		bool gShader;
		const char* gShaderCode;
		std::string vPath;
		std::string fPath;

	};
}

