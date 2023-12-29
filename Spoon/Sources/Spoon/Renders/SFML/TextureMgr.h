#pragma once

#include "Core/Core.h"
#include <SFML/Graphics.hpp>
#include <snpch.h>

class TextureMgr
{

public:
	TextureMgr() {}
	TextureMgr(const TextureMgr&) = delete;
	TextureMgr& operator=(const TextureMgr&) = delete;
	~TextureMgr() {}

	bool LoadTexture(const std::string& name, std::string& fileName, sf::Texture& texture);
	sf::Texture& GetTexture(const std::string& name);

	void LoadFont(const std::string& name, const std::string& fileName);
	sf::Font& GetFont(const std::string& name);

private:
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;

};