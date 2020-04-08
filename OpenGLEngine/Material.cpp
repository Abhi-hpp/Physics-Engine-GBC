#include "Material.h"
namespace Reality
{
	Material::Material(Shader* _shader) : shader(_shader)
	{
		dirty = true;
	}
	void Material::Init()
	{
		if (dirty)
		{
			// compile shaders
			unsigned int vertex, fragment;
			// vertex shader
			vertex = glCreateShader(GL_VERTEX_SHADER);
			std::string v = shader->vShaderCode;
			std::string f = shader->fShaderCode;

			glShaderSource(vertex, 1, &shader->vShaderCode, NULL);
			glCompileShader(vertex);
			checkCompileErrors(vertex, "VERTEX");
			// fragment Shader
			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &shader->fShaderCode, NULL);
			glCompileShader(fragment);
			checkCompileErrors(fragment, "FRAGMENT");
			// if geometry shader is given, compile geometry shader
			unsigned int geometry;
			if (shader->gShader)
			{
				geometry = glCreateShader(GL_GEOMETRY_SHADER);
				glShaderSource(geometry, 1, &shader->gShaderCode, NULL);
				glCompileShader(geometry);
				checkCompileErrors(geometry, "GEOMETRY");
			}
			// shader Program
			ID = glCreateProgram();
			glAttachShader(ID, vertex);
			glAttachShader(ID, fragment);
			if (shader->gShader)
				glAttachShader(ID, geometry);
			glLinkProgram(ID);
			checkCompileErrors(ID, "PROGRAM");
			
			// delete the shaders as they're linked into our program now and no longer necessery
			glDeleteShader(vertex);
			glDeleteShader(fragment);
			if (shader->gShader)
				glDeleteShader(geometry);

			// Set properties
			glUseProgram(ID);
			setFloat("material.shininess", shininess);

			//// Set textures
			//for (unsigned int i = 0; i < diffuseTextures.size(); i++)
			//{
			//	glUniform1i(glGetUniformLocation(ID, "material.diffuse"), i);
			//}
			//// set textures
			//for (unsigned int i = 0; i < specularMaps.size(); i++)
			//{
			//	glUniform1i(glGetUniformLocation(ID, "material.specular"), i);
			//}
			dirty = false;
		}
	}

	void Material::use() 
	{	
		glUseProgram(ID);

		// Set textures
		for (unsigned int i = 0; i < diffuseTextures.size(); i++)
		{
			if (diffuseTextures[i]->WasLoadedSuccessfully())
			{
				glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
				glBindTexture(GL_TEXTURE_2D, diffuseTextures[i]->GetId());
				glUniform1i(glGetUniformLocation(ID, "material.diffuse"), i);
			}
			else
			{
				std::cout << "Diffuse Texture not loaded " << diffuseTextures[i]->path << std::endl;
			}
		}
		// set textures
		for (unsigned int i = 0; i < specularMaps.size(); i++)
		{
			if (specularMaps[i]->WasLoadedSuccessfully())
			{
				glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
				glUniform1i(glGetUniformLocation(ID, "material.specular"), i);
				glBindTexture(GL_TEXTURE_2D, specularMaps[i]->GetId());
			}
			else
			{
				std::cout << "Specular Texture not loaded " << specularMaps[i]->path << std::endl;
			}
		}
		//// set textures
		//for (unsigned int i = 0; i < diffuseTextures.size(); i++)
		//{
		//	
		//}
		//// set textures
		//for (unsigned int i = 0; i < specularMaps.size(); i++)
		//{
		//}
		glUseProgram(ID);

	}

	void Material::checkCompileErrors(GLuint shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
}