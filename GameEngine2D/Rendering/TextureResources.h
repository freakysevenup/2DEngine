#pragma once
#include "Texture.h"
#include <map>

class TextureResources
{
public:
	TextureResources() {}
	~TextureResources();

	Texture * Load(const std::string& filePath);
	void Free(const std::string& filePath);
	void Register(const std::string& filePath, Texture* texture);
	void UnRegister(const std::string& filePath);
	Texture * Get(const std::string& filePath);

private:
	typedef std::map <std::string, Texture*> TextureMap;
	TextureMap m_textures;
};

