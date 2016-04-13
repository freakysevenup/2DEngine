#pragma once
#include <string>
#include <map>
#include "Texture.h"

class TextureMap
{
public:
	TextureMap() {}
	~TextureMap() {}

	Texture GetTexture(const std::string& texturePath);

private:
	Texture LoadPNG(const std::string& name);
	std::map<std::string, Texture> m_textureMap;
};

