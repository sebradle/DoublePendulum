#pragma once
#include <string>
#include <GL/glew.h>
namespace Engine {
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertShaderFilePath, const std::string& fragShaderFilePath);

		void linkShaders();

		void addAttribute(const std::string& attributeName);

		GLint getUniformLocation(const std::string& uniformName);

		void use();
		void unuse();

	private:
		GLuint mProgramID;
		GLuint mVertShaderID;
		GLuint mFragShaderID;
		int mNumAttributes;

		void compileShader(const std::string& filePath, GLuint shaderID);
	};

}