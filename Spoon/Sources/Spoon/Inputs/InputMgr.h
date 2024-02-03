#pragma once

#include "PlayerInputAction.h"

#include <map>
#include <vector>
#include <functional>
#include <SFML/Window/Keyboard.hpp>

enum class InputAction;

struct InputBindInfo
{
	InputBindInfo(unsigned playerIndex, InputAction action, sf::Keyboard::Key key);
	unsigned PlayerIndex;
	InputAction Action;
	sf::Keyboard::Key Key;
};

class InputMgr final
{
public:
	bool Init();
	bool Update(float fDeltaTime);
	bool Reset();

	void AddNewPlayer();

	void BindAction(int playerIndex, InputAction inputAction, std::function<void(float)> func, InputType inputType);

private:

	void SetPlayerActionState(unsigned playerIndex, InputAction action, float value);

	std::vector<PlayerInputAction> PlayersInputAction;
	std::map<int,std::vector<InputBindInfo>> InputBinds;
};