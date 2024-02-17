#pragma once

#include "PlayerInputAction.h"
#include <map>
#include <vector>
#include <functional>
#include <SFML/Window/Keyboard.hpp>

enum class InputAction;

struct InputBindInfo
{
	InputBindInfo(unsigned PlayerIndex, InputAction Action, sf::Keyboard::Key Key);
	unsigned PlayerIndex;
	InputAction Action;
	sf::Keyboard::Key Key;
};

class InputMgr final
{
	public:
		bool Init();
		bool Update(float DeltaTime);
		bool Reset();

		void AddNewPlayer();

		void BindAction(int PlayerIndex, InputAction InputAction, const std::function<void(float)>& Func, InputType InputType);

	private:

		void SetPlayerActionState(unsigned PlayerIndex, InputAction Action, float Value);

		std::vector<PlayerInputAction> PlayersInputAction;
		std::map<int,std::vector<InputBindInfo>> InputBinds;
};