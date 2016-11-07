#include "GLSLProgram.h"
#include "Errors.h"

#include <fstream>
#include <vector>


namespace Engine 
{
	GLSLProgram::GLSLProgram() : _numAttrib(0), _programID(0), _vertexID(0), _fragmentID(0)
	{
	}

	GLSLProgram::~GLSLProgram()
	{
	}

	void GLSLProgram::compileShaders(const std::string vertexFilePath, const std::string fragmentFilePath) {
		//Link Vertex and fragment shader if successfully compiled.
		//Get a program object.
		_programID = glCreateProgram();

		_vertexID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertexID == 0) {
			fatalError("Vertex shader failed to be created!");
		}

		_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragmentID == 0) {
			fatalError("Fragment shader failed to be created!");
		}

		compileShader(vertexFilePath, _vertexID);
		compileShader(fragmentFilePath, _fragmentID);
	}

	void GLSLProgram::addAttribute(const std::string attributeName) {
		glBindAttribLocation(_programID, _numAttrib++, attributeName.c_str());
	}

	GLint GLSLProgram::getUniformLocation(const std::string& uniformName) {
		GLint location = glGetUniformLocation(_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX) {
			fatalError("Uniform " + uniformName + " not found in shader!");
		}
		return location;
	}

	void GLSLProgram::linkShaders() {

		//Attach shaders to program
		glAttachShader(_programID, _vertexID);
		glAttachShader(_programID, _fragmentID);

		//Link program
		glLinkProgram(_programID);

		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

			//Don't need program anymore.
			glDeleteProgram(_programID);
			//Don't leak shaders.
			glDeleteShader(_vertexID);
			glDeleteShader(_fragmentID);

			//print the error log and quit
			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shaders failed to link!");
		}

		//Always detach shaders after a successful link.
		glDetachShader(_programID, _vertexID);
		glDetachShader(_programID, _fragmentID);
		glDeleteShader(_vertexID);
		glDeleteShader(_fragmentID);
	}

	void GLSLProgram::use() {
		glUseProgram(_programID);
		for (int i = 0; i < _numAttrib; i++) {
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unuse() {
		glUseProgram(0);
	}

	void GLSLProgram::compileShader(const std::string filePath, GLuint &id) {
		std::ifstream vertexFile(filePath);
		if (vertexFile.fail()) {
			perror(filePath.c_str());
			fatalError("Failed to open " + filePath);
		}

		std::string fileContents = "";
		std::string line;

		while (std::getline(vertexFile, line)) {
			fileContents += line + "\n";
		}

		vertexFile.close();

		const char* contentsPtr = fileContents.c_str();
		glShaderSource(id, 1, &contentsPtr, nullptr);

		glCompileShader(id);

		//Error check
		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			//Exit with th failure.
			glDeleteShader(id);

			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shader " + filePath + "failed to compile");

			return;
		}
	}

}
