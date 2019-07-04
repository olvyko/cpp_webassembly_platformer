
#ifndef GLSL_PROGRAM_H
#define GLSL_PROGRAM_H

#include <string>
#include <GL/glew.h>

//This class handles the compilation, linking, and usage of a GLSL shader program.
//Reference: http://www.opengl.org/wiki/Shader_Compilation
class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string& t_vertexShaderFilePath, const std::string& t_fragmentShaderFilePath);

	void compileShadersFromSource(const char* t_vertexSource, const char* t_fragmentSource);

	void linkShaders();

	void addAttribute(const std::string& t_attributeName);

	GLint getUniformLocation(const std::string& t_uniformName);

	void use();
	void unuse();

	void dispose();
private:

	int m_numAttributes;

	void compileShader(const char* t_source, const std::string& t_name, GLuint t_id);

	GLuint m_programID;

	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;
};

#endif // GLSL_PROGRAM_H
