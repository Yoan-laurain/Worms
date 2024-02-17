#include "InputMgr.h"

#include "InputAction.h"

#include <SFML/Window/Keyboard.hpp>
#include <assert.h>

bool InputMgr::Init()
{
	return true;
}

bool InputMgr::Update(float fDeltaTime)
{
	for (const auto& p : InputBinds)
	{
		for (const auto& inputBind : p.second)
		{
			const sf::Keyboard::Key& key = inputBind.Key;
		
			if (sf::Keyboard::isKeyPressed(key))
			{
				SetPlayerActionState(inputBind.PlayerIndex, inputBind.Action, 1.f);
			}
			else
			{				
				SetPlayerActionState(inputBind.PlayerIndex, inputBind.Action, 0.f);
			}
		}	
	}

	return true;
}

bool InputMgr::Reset()
{
	return false;
}

void InputMgr::AddNewPlayer()
{
	unsigned int index = PlayersInputAction.size();
	PlayersInputAction.push_back(PlayerInputAction(index));

#define INIT_DEFAULT_BIND(key, bind) InputBinds[key].push_back(bind);
#include "Player0KeyboardDefaultBind.h"
#undef INIT_DEFAULT_BIND
	
}

void InputMgr::BindAction(int playerIndex, InputAction inputAction, std::function<void(float)> func, InputType inputType)
{
	PlayersInputAction[playerIndex].BindAction(inputAction, func,inputType);
}

void InputMgr::SetPlayerActionState(unsigned playerIndex, InputAction action, float value)
{
#if _DEBUG
	assert(playerIndex < PlayersInputAction.size());
#endif

	InputActionInfo& info = PlayersInputAction[playerIndex].InputActionsInfo.at(action);

	if (value != 0.f)
		PlayersInputAction[playerIndex].SetInputAction(action, value);
	else if (value == 0.f && info.HasBeenPressed)
	{
		PlayersInputAction[playerIndex].OnReleased(action);
		info.HasBeenPressed = false;
	}
}

InputBindInfo::InputBindInfo(unsigned playerIndex, InputAction action, sf::Keyboard::Key key)
	: PlayerIndex(playerIndex), Action(action), Key(key)
{
}
