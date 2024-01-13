#pragma once

#include <SFML/Graphics.hpp>

class TextureMgr
{

public:
	TextureMgr() = default;
	TextureMgr(const TextureMgr&) = delete;
	TextureMgr& operator=(const TextureMgr&) = delete;
	~TextureMgr() = default;

	bool LoadTexture(const std::string& name, std::string& fileName);
	sf::Texture& GetTexture(const std::string& name);
	bool IsTextureLoaded(const std::string& name);

	void LoadFont(const std::string& name, const std::string& fileName);
	sf::Font& GetFont(const std::string& name);
	bool IsFontLoaded(const std::string& name);

private:
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;

};