#include "TextureResources.h"

TextureMap TextureResources::m_textureMap;

Texture TextureResources::GetTexture(const std::string& name)
{
	return m_textureMap.GetTexture(name);
}
