#pragma once

#include <SFML/Graphics.hpp>

class TextureMgr
{
	public:
		TextureMgr() = default;
		TextureMgr(const TextureMgr&) = delete;
		TextureMgr& operator=(const TextureMgr&) = delete;
		~TextureMgr() = default;

		bool LoadTexture(const std::string& Name, const std::string& FileName);
		sf::Texture& GetTexture(const std::string& Name);
		bool IsTextureLoaded(const std::string& Name) const;

		void LoadFont(const std::string& Name, const std::string& FileName);
		sf::Font& GetFont(const std::string& Name);
		bool IsFontLoaded(const std::string& Name) const;

	private:
		std::map<std::string, sf::Texture> Textures;
		std::map<std::string, sf::Font> Fonts;
};