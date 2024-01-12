#include "TextureMgr.h"

bool TextureMgr::LoadTexture(const std::string& name, std::string& fileName)
{
	if (IsTextureLoaded(name))
	{
		return true;
	}

	sf::Texture texture;

	if ( texture.loadFromFile(fileName) )
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

bool TextureMgr::IsTextureLoaded(const std::string& name)
{
	if (_textures.find(name) == _textures.end())
	{
		return false;
	}
	return true;
}

void TextureMgr::LoadFont(const std::string& name, const std::string& fileName)
{
	// if already loaded, do nothing
	if (_fonts.find(name) != _fonts.end())
	{
		return;
	}

	sf::Font font;

	if (font.loadFromFile(fileName))
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