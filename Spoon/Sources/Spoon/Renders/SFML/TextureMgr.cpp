#include "TextureMgr.h"

bool TextureMgr::LoadTexture(const std::string& Name, const std::string& FileName)
{
	if (IsTextureLoaded(Name))
	{
		return true;
	}

	sf::Texture Texture;

	if ( Texture.loadFromFile(FileName) )
	{
		Textures[Name] = Texture;
	}
	else
	{
		throw std::runtime_error("Error loading texture: " + FileName);
	}
	return true;
}

sf::Texture& TextureMgr::GetTexture(const std::string& Name)
{
	if (!IsTextureLoaded(Name))
	{
		throw std::runtime_error("Error texture not found: " + Name);
	}

	return Textures.at(Name);
}

bool TextureMgr::IsTextureLoaded(const std::string& Name) const
{
	return Textures.contains(Name);
}

void TextureMgr::LoadFont(const std::string& Name, const std::string& FileName)
{
	if ( IsFontLoaded(Name) )
	{
		return;
	}

	sf::Font Font;

	if (Font.loadFromFile(FileName))
	{
		Fonts[Name] = Font;
	}
	else
	{
		throw std::runtime_error("Error loading font: " + FileName);
	}
}

sf::Font& TextureMgr::GetFont(const std::string& Name)
{
	if (!Fonts.contains(Name))
	{
		throw std::runtime_error("Error font not found: " + Name);
	}

	return Fonts.at(Name);
}

bool TextureMgr::IsFontLoaded(const std::string& Name) const
{
	return Fonts.contains(Name);
}