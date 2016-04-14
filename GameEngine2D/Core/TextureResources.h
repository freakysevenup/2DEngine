#pragma once
#include "Texture.h"
#include "TextureMap.h"
#include <map>

class TextureResources
{
public:

	static Texture GetTexture(const std::string& name);

private:

	static TextureMap m_textureMap;
};

