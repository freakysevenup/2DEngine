#pragma once
#include <glew\glew.h>
#include <string>
#include "..\Core\Reference.h"

class Texture : public Reference
{
public:

	Texture() {}
	~Texture() {}

	GLuint m_id;
	GLint m_height;
	GLint m_width;
	std::string m_filePath;
	GLint m_numComponents;
};

