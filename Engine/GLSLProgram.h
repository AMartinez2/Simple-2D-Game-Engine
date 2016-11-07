#pragma once

#include <GL/glew.h>
#include <string>

namespace Engine {
	class GLSLProgram
	{
	public:

		GLSLProgram();
		~GLSLProgram();
		void compileShaders(const std::string vertexFilePath, const std::string fragmentFilePath);
		void addAttribute(const std::string attributeName);
		GLint getUniformLocation(const std::string& uniformName);
		void linkShaders();
		void use();
		void unuse();

	private:

		GLuint _programID;
		GLuint _vertexID;
		GLuint _fragmentID;
		int _numAttrib;
		void compileShader(const std::string filePath, GLuint& id);

	};

}