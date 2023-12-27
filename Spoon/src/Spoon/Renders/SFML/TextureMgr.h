#pragma once
#include "Spoon/Core/Core.h"
#include <snpch.h>
#include <SFML/Graphics/Texture.hpp>

class TextureMgr
{

public:

	TextureMgr() : TextureRef(nullptr) {};
	virtual ~TextureMgr() {};

	TextureMgr(const TextureMgr&) = delete;

	static TextureMgr& GetManager() { return ManagerInstance; };

	sf::Texture* GetTexture() const { return TextureRef; };

	bool LoadTexture(const std::filesystem::path& path);

private:

	sf::Texture* TextureRef;

	static TextureMgr ManagerInstance;

};