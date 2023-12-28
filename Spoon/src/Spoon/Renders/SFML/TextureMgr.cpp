#include "TextureMgr.h"

bool TextureMgr::LoadTexture(const std::string& name, std::string& fileName, sf::Texture& texture)
{
	if (_textures.find(name) != _textures.end())
	{
		texture = GetTexture(name);
		return true;
	}

	if (texture.loadFromFile(fileName))
	{
		_textures[name] = texture;
	}
	else
	{
		throw std::runtime_error("Error loading texture: " + fileName);
		return false;
	}
	return true;
}

sf::Texture& TextureMgr::GetTexture(const std::string& name)
{
	if (_textures.find(name) == _textures.end())
	{
		throw std::runtime_error("Error texture not found: " + name);
	}

	return _textures.at(name);
}

void TextureMgr::LoadFont(const std::string& name, const std::string& fileName)
{
	if (sf::Font font; font.loadFromFile(fileName))
	{
		_fonts[name] = font;
	}
	else
	{
		throw std::runtime_error("Error loading font: " + fileName);
	}
}

sf::Font& TextureMgr::GetFont(const std::string& name)
{
	if (_fonts.find(name) == _fonts.end())
	{
		throw std::runtime_error("Error font not found: " + name);
	}

	return _fonts.at(name);
}