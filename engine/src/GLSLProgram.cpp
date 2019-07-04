#include "GLSLProgram.h"
#include "GameErrors.h"
#include "IOManager.h"

#include <vector>

#include <fstream>

GLSLProgram::GLSLProgram() : 
	m_numAttributes(0), 
	m_programID(0), 
	m_vertexShaderID(0), 
	m_fragmentShaderID(0)
{
}

GLSLProgram::~GLSLProgram()
{
}

//Compiles the shaders into a form that your GPU can understand
void GLSLProgram::compileShaders(const std::string& t_vertexShaderFilePath, const std::string& t_fragmentShaderFilePath) 
{
	std::string vertSource;
	std::string fragSource;

	IOManager::getInstance()->readFileToBuffer(t_vertexShaderFilePath, vertSource);
	IOManager::getInstance()->readFileToBuffer(t_fragmentShaderFilePath, fragSource);

	compileShadersFromSource(vertSource.c_str(), fragSource.c_str());
}

void GLSLProgram::compileShadersFromSource(const char* t_vertexSource, const char* t_fragmentSource)
{
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	m_programID = glCreateProgram();

	//Create the vertex shader object, and store its ID
	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (m_vertexShaderID == 0) 
	{
		fatalError("Vertex shader failed to be created!");
	}

	//Create the fragment shader object, and store its ID
	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (m_fragmentShaderID == 0) 
	{
		fatalError("Fragment shader failed to be created!");
	}

	//Compile each shader
	compileShader(t_vertexSource, "Vertex Shader", m_vertexShaderID);
	compileShader(t_fragmentSource, "Fragment Shader", m_fragmentShaderID);
}

void GLSLProgram::linkShaders() 
{
	// Attach our shaders to our program
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);

	// Link our program
	glLinkProgram(m_programID);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(m_programID);
		// Don't leak shaders either.
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);

		// print the error log and quit
		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shaders failed to link!");
	}

	// Always detach shaders after a successful link.
	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
}

// Adds an attribute to our shader. SHould be called between compiling and linking.
void GLSLProgram::addAttribute(const std::string& t_attributeName)
{
	glBindAttribLocation(m_programID, m_numAttributes++, t_attributeName.c_str());
}

GLint GLSLProgram::getUniformLocation(const std::string& t_uniformName)
{
	GLint location = glGetUniformLocation(m_programID, t_uniformName.c_str());
	if (location == GL_INVALID_INDEX) 
	{
		fatalError("Uniform " + t_uniformName + " not found in shader!");
	}
	return location;
}

// enable the shader, and all its attributes
void GLSLProgram::use() 
{
	glUseProgram(m_programID);
	//enable all the attributes we added with addAttribute
	for (int i = 0; i < m_numAttributes; i++) 
	{
		glEnableVertexAttribArray(i);
	}
}

// disable the shader
void GLSLProgram::unuse() 
{
	glUseProgram(0);
	for (int i = 0; i < m_numAttributes; i++) 
	{
		glDisableVertexAttribArray(i);
	}
}

void GLSLProgram::dispose() 
{
	if (m_programID)
	{
		glDeleteProgram(m_programID);
	}
}

// Compiles a single shader file
void GLSLProgram::compileShader(const char* t_source, const std::string& t_name, GLuint t_id)
{
	// tell opengl that we want to use fileContents as the contents of the shader file
	glShaderSource(t_id, 1, &t_source, nullptr);

	
	// compile the shader
	glCompileShader(t_id);

	// check for errors
	GLint success = 0;
	glGetShaderiv(t_id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(t_id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(t_id, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(t_id); //Don't leak the shader.

		// Print error log and quit
		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shader " + t_name + " failed to compile");
	}
}
