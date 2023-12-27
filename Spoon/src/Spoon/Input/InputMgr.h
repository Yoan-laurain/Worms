#pragma once

#include "PlayerInputAction.h"

#include <map>
#include <vector>
#include <functional>
#include <SFML/Window/Keyboard.hpp>

enum class InputAction;

class InputMgr final
{
public:
	bool Init();
	bool Update(float fDeltaTime);
	bool Reset();

	void AddNewPlayer();

	void BindAction(int playerIndex, InputAction inputAction, std::function<void(float)> func);

private:

	struct InputBindInfo
	{
		InputBindInfo(unsigned playerIndex, InputAction action);
		unsigned PlayerIndex;
		InputAction Action;
	};

	void SetPlayerActionState(unsigned playerIndex, InputAction action, float value);

	std::vector<PlayerInputAction> PlayersInputAction;
	std::map<sf::Keyboard::Key, InputBindInfo> InputBinds;
};