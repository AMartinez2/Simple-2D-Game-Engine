#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace Engine {
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}


	GLTexture TextureCache::getTexture(std::string texturePath) {

		//Map iterator
		//lookup the texture and see if its in the map
		auto mit = _textureMap.find(texturePath);

		//check if its not int he map
		if (mit == _textureMap.end()) {
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			std::pair<std::string, GLTexture> newPair(texturePath, newTexture);

			//Insert it into the map
			_textureMap.insert(make_pair(texturePath, newTexture));

			//std::cout << "Loaded Texture!\n";
			return newTexture;
		}
		//std::cout << "loaded cache texture!\n";
		return mit->second;

	}
}