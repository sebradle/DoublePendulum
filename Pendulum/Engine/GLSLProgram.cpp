#include "GLSLProgram.h"
#include "Errors.h"
#include <fstream>
#include <vector>
namespace Engine {
	GLSLProgram::GLSLProgram() : mProgramID(0), mVertShaderID(0), mFragShaderID(0), mNumAttributes(0)
	{
	}


	GLSLProgram::~GLSLProgram()
	{
	}


	void GLSLProgram::compileShaders(const std::string& vertShaderFilePath, const std::string& fragShaderFilePath) {


		mProgramID = glCreateProgram();

		// Create Vert Shader
		mVertShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (mVertShaderID == 0) {
			fatalError("Vertex shader failed to be created");
		}

		// Create Frag Shader
		mFragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (mFragShaderID == 0) {
			fatalError("Fragment shader failed to be created");
		}

		// Compile Shaders
		compileShader(vertShaderFilePath, mVertShaderID);
		compileShader(fragShaderFilePath, mFragShaderID);
	}

	void GLSLProgram::linkShaders() {

		//Attach our shaders to our program
		glAttachShader(mProgramID, mVertShaderID);
		glAttachShader(mProgramID, mFragShaderID);

		//Link our program
		glLinkProgram(mProgramID);

		//Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(mProgramID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(mProgramID, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetProgramInfoLog(mProgramID, maxLength, &maxLength, &errorLog[0]);

			//We don't need the program anymore.
			glDeleteProgram(mProgramID);
			//Don't leak shaders either.
			glDeleteShader(mVertShaderID);
			glDeleteShader(mFragShaderID);

			std::printf("%s\n", &errorLog[0]);
			fatalError("Shaders failed to link");
		}

		//Always detach shaders after a successful link.
		glDetachShader(mProgramID, mVertShaderID);
		glDetachShader(mProgramID, mFragShaderID);
		glDeleteShader(mVertShaderID);
		glDeleteShader(mFragShaderID);
	}

	void GLSLProgram::addAttribute(const std::string& attributeName) {
		glBindAttribLocation(mProgramID, mNumAttributes++, attributeName.c_str());
	}

	GLint GLSLProgram::getUniformLocation(const std::string& uniformName) {
		GLint location = glGetUniformLocation(mProgramID, uniformName.c_str());
		if (location == GL_INVALID_INDEX) {
			fatalError("Uniform " + uniformName + " not found");
		}
		return location;
	}

	void GLSLProgram::use() {
		glUseProgram(mProgramID);
		for (int i = 0; i < mNumAttributes; i++) {
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unuse() {
		glUseProgram(0);
		for (int i = 0; i < mNumAttributes; i++) {
			glDisableVertexAttribArray(i);
		}
	}

	void GLSLProgram::compileShader(const std::string& filePath, GLuint shaderID) {
		// Read in contents of shader and compile
		std::ifstream file(filePath);
		if (file.fail()) {
			perror(filePath.c_str());
			fatalError("Failed to open" + filePath);
		}

		std::string fileContents = "";
		std::string line;

		while (std::getline(file, line)) {
			fileContents += line + "\n";
		}

		file.close();

		const char* contentsPtr = fileContents.c_str();
		glShaderSource(shaderID, 1, &contentsPtr, nullptr);
		glCompileShader(shaderID);


		// Check if shader compiled
		GLint success = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(shaderID);
			std::printf("%s\n", &errorLog[0]);
			fatalError("Shader " + filePath + " failed to compile");
		}
	}
}