#pragma once
#include <glew\glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm\glm.hpp>
using namespace glm;

class Shader
{
public:
	Shader() {}
	~Shader() {}
	Shader(const Shader &other)
	{
		m_program = other.m_program;
	}
	Shader operator =(const Shader &param) const
	{
		return Shader(param);
	}

	void Init(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath = nullptr);
	void checkCompileErrors(GLuint shader, const std::string& type);

	void Begin();

	void SetUniformiARB(const std::string & uniformName, const GLint & value)
	{
		glUniform1iARB(glGetUniformLocation(this->m_program, uniformName.c_str()), value);
	}
	void SetUniformfARB(const std::string & uniformName, const GLfloat & value)
	{
		glUniform1fARB(glGetUniformLocation(this->m_program, uniformName.c_str()), value);
	}
	void SetUniform2fvARB(const std::string & uniformName, const vec2 & value)
	{
		glUniform2fvARB(glGetUniformLocation(this->m_program, uniformName.c_str()), 1, &value[0]);
	}
	void SetUniform3fvARB(const std::string & uniformName, const vec3 & value)
	{
		glUniform3fvARB(glGetUniformLocation(this->m_program, uniformName.c_str()), 1, &value[0]);
	}
	void SetUniform4fvARB(const std::string & uniformName, const vec4 & value)
	{
		glUniform4fvARB(glGetUniformLocation(this->m_program, uniformName.c_str()), 1, &value[0]);
	}
	void SetUniformMatrix3fvARB(const std::string & uniformName, const mat3 & value)
	{
		glUniformMatrix3fvARB(glGetUniformLocation(this->m_program, uniformName.c_str()), 1, GL_FALSE, &value[0][0]);
	}
	void SetUniformMatrix4fvARB(const std::string & uniformName, const mat4 & value)
	{
		glUniformMatrix4fvARB(glGetUniformLocation(this->m_program, uniformName.c_str()), 1, GL_FALSE, &value[0][0]);
	}

private:

	GLint m_program;
};

