#include "PlayerInputAction.h"
#include "./Enums/InputAction.h"
#include "./Enums/InputType.h"

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
	
	if (info.InputType == InputType::Pressed && info.HasBeenPressed)
		return;

	info.Value = value;
	for (auto callback : info.Callbacks)
	{
		callback(value);
	}

	info.HasBeenPressed = true;
}

void PlayerInputAction::OnReleased(InputAction action)
{
	InputActionInfo& info = InputActionsInfo.at(action);
	info.HasBeenPressed = false;
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

void PlayerInputAction::BindAction(InputAction inputAction, std::function<void(float)> func, InputType inputType)
{
	InputActionsInfo.at(inputAction).Callbacks.push_back(func);
	InputActionsInfo.at(inputAction).InputType = inputType;
}

InputActionInfo::InputActionInfo(): Value(0.f), InputType(), HasBeenPressed(false)
{
}