#include "TextureResources.h"
#include <iostream>
#include "picoPNG.h"
#include <glew\glew.h>
#include "Utility.h"
#include "Texture.h"
#include "ErrorLog.h"

TextureResources::~TextureResources()
{
	TextureMap::iterator it;
	for (it = m_textures.begin(); it != m_textures.end(); ++it)
	{
		delete (*it).second;
	}
}

Texture * TextureResources::Load(const std::string& filePath)
{
	Texture * texture = new Texture();

	std::vector<unsigned char> in;
	std::vector<unsigned char> out;
	unsigned long width, height;

	if (!Utility::readFileToBuffer(filePath, in))
	{
		ErrorLog::GetInstance()->Log(ErrorLog::SeverityLevel::JADE_ERROR, "Failed to load PNG file " + filePath + " to buffer!");
	}


	int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
	if (errorCode != 0)
	{
		ErrorLog::GetInstance()->Log(ErrorLog::SeverityLevel::JADE_ERROR, "decodePNG failed with error: " + std::to_string(errorCode));
	}

	glGenTextures(1, &(texture->m_id));
	glBindTexture(GL_TEXTURE_2D, texture->m_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	texture->m_width = width;
	texture->m_height = height;

	Register(filePath, texture);

	ErrorLog::GetInstance()->Log(ErrorLog::SeverityLevel::JADE_INFO, filePath + " Texture Loaded");

	return texture;
}

void TextureResources::Free(const std::string& filePath)
{
	UnRegister(filePath);
	glDeleteTextures(1, &Get(filePath)->m_id);
	ErrorLog::GetInstance()->Log(ErrorLog::SeverityLevel::JADE_INFO, filePath + " Texture Freed");
}

void TextureResources::Register(const std::string& name, Texture* resource)
{
	TextureMap::iterator it = m_textures.find(name);
	if (it == m_textures.end())
	{
		m_textures.insert(std::make_pair(name, resource));
	}
}

void TextureResources::UnRegister(const std::string& name)
{
	TextureMap::iterator it = m_textures.find(name);
	if (it != m_textures.end())
	{
		it->second->removeReference();
		m_textures.erase(it);
	}
}

Texture * TextureResources::Get(const std::string& name)
{
	TextureMap::iterator it = m_textures.find(name);
	if (it != m_textures.end())
	{
		(*it).second->addReference();
		return (*it).second;
	}
	return nullptr;
}