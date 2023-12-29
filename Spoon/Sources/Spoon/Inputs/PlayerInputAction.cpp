#include "PlayerInputAction.h"

#include "InputAction.h"

#include <iostream>

PlayerInputAction::PlayerInputAction(unsigned playerIndex): PlayerIndex(playerIndex)
{
	for (unsigned i = 0; i < (unsigned) InputAction::Num; ++i)
	{
		InputAction action = static_cast<InputAction>(i);
		InputActionsInfo.emplace(action, InputActionInfo());
	}
}

void PlayerInputAction::SetInputAction(InputAction action, float value)
{
	InputActionInfo& info = InputActionsInfo.at(action);

#if _DEBUG
	//std::cout << "Player " << PlayerIndex << ", Action: " << (int) action << ", Update: " << value << std::endl;
#endif

	info.Value = value;
	for (auto callback : info.Callbacks)
	{
		callback(value);
	}
}

float PlayerInputAction::GetInputActionValue(InputAction action) const
{
	return InputActionsInfo.at(action).Value;
}

bool PlayerInputAction::IsInputActionPressed(InputAction action) const
{
	return InputActionsInfo.at(action).Value != 0.f;
}

bool PlayerInputAction::IsInputActionReleased(InputAction action) const
{
	return InputActionsInfo.at(action).Value == 0.f;
}

void PlayerInputAction::BindAction(InputAction inputAction, std::function<void(float)> func)
{
	InputActionsInfo.at(inputAction).Callbacks.push_back(func);
}

PlayerInputAction::InputActionInfo::InputActionInfo(): Value(0.f), Callbacks()
{}
