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
	//for (const auto& p : InputBinds)
	//{
	//	const sf::Keyboard::Key& key = p.first;
	//	const InputBindInfo& bindInfo = p.second;

	//	if (sf::Keyboard::isKeyPressed(key))
	//	{
	//		SetPlayerActionState(bindInfo.PlayerIndex, bindInfo.Action, 1.f);
	//	}
	//	else
	//	{
	//		SetPlayerActionState(bindInfo.PlayerIndex, bindInfo.Action, 0.f);
	//	}
	//}

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

	if (index == 0)
	{
#define INIT_DEFAULT_BIND(key, bind) InputBinds.insert(std::make_pair(key, bind));
#include "Player0KeyboardDefaultBind.h"
#undef INIT_DEFAULT_BIND
	}
}

void InputMgr::BindAction(int playerIndex, InputAction inputAction, std::function<void(float)> func)
{
	PlayersInputAction[playerIndex].BindAction(inputAction, func);
}

void InputMgr::SetPlayerActionState(unsigned playerIndex, InputAction action, float value)
{
#if _DEBUG
	assert(playerIndex < PlayersInputAction.size());
#endif

	PlayersInputAction[playerIndex].SetInputAction(action, value);
}

InputMgr::InputBindInfo::InputBindInfo(unsigned playerIndex, InputAction action): PlayerIndex(playerIndex), Action(action)
{}
