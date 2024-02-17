#include "InputMgr.h"
#include "./Enums/InputAction.h"
#include <SFML/Window/Keyboard.hpp>
#include <cassert>

bool InputMgr::Init()
{
	return true;
}

bool InputMgr::Update(float fDeltaTime)
{
	for (const auto& P : InputBinds)
	{
		for (const auto& InputBind : P.second)
		{
			const sf::Keyboard::Key& Key = InputBind.Key;
		
			if (sf::Keyboard::isKeyPressed(Key))
			{
				SetPlayerActionState(InputBind.PlayerIndex, InputBind.Action, 1.f);
			}
			else
			{				
				SetPlayerActionState(InputBind.PlayerIndex, InputBind.Action, 0.f);
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
	PlayersInputAction.emplace_back();

#define INIT_DEFAULT_BIND(key, bind) InputBinds[key].push_back(bind);
#include "Player0KeyboardDefaultBind.h"
#undef INIT_DEFAULT_BIND
}

void InputMgr::BindAction(const int PlayerIndex, const InputAction InputAction, const std::function<void(float)>& Func, const InputType InputType)
{
	PlayersInputAction[PlayerIndex].BindAction(InputAction, Func,InputType);
}

void InputMgr::SetPlayerActionState(const unsigned PlayerIndex, const InputAction Action, const float Value)
{
#if _DEBUG
	assert(PlayerIndex < PlayersInputAction.size());
#endif

	InputActionInfo& Info = PlayersInputAction[PlayerIndex].InputActionsInfo.at(Action);

	if (Value != 0.f)
	{
		PlayersInputAction[PlayerIndex].SetInputAction(Action, Value);
	}
	else if (Value == 0.f && Info.HasBeenPressed)
	{
		PlayersInputAction[PlayerIndex].OnReleased(Action);
		Info.HasBeenPressed = false;
	}
}

InputBindInfo::InputBindInfo(const unsigned PlayerIndex, const InputAction Action, const sf::Keyboard::Key Key)
	: PlayerIndex(PlayerIndex), Action(Action), Key(Key)
{
}