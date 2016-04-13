#include "TextureMap.h"
#include <vector>
#include "Utility.h"
#include "ErrorLog.h"
#include <glew\glew.h>
#include "picoPNG.h"

Texture TextureMap::LoadPNG(const std::string& name)
{
	Texture texture = {};

	std::vector<unsigned char> in;
	std::vector<unsigned char> out;
	unsigned long width, height;

	if (!Utility::readFileToBuffer(name, in))
	{
		ErrorLog::GetInstance()->Log(ErrorLog::SeverityLevel::JADE_ERROR, "Failed to load PNG file " + name + " to buffer!");
	}


	int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
	if (errorCode != 0)
	{
		ErrorLog::GetInstance()->Log(ErrorLog::SeverityLevel::JADE_ERROR, "decodePNG failed with error: " + std::to_string(errorCode));
	}

	glGenTextures(1, &(texture.m_id));
	glBindTexture(GL_TEXTURE_2D, texture.m_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	texture.m_width = width;
	texture.m_height = height;
	return texture;
}

Texture TextureMap::GetTexture(const std::string& texturePath)
{
	//The following will look up the texture and check if it is in the map
	auto mit = m_textureMap.find(texturePath);

	//check if its not in the map
	if (mit == m_textureMap.end())
	{
		//Load the texture
		Texture newTexture = LoadPNG(texturePath);

		//Insert it into the texture
		m_textureMap.insert(make_pair(texturePath, newTexture));

		return newTexture;
	}
	return mit->second;
}