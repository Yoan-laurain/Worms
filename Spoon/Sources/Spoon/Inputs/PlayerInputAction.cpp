#include "PlayerInputAction.h"
#include "./Enums/InputAction.h"
#include "./Enums/InputType.h"

PlayerInputAction::PlayerInputAction()
{
	for (unsigned i = 0; i < static_cast<unsigned>(InputAction::Num); ++i)
	{
		InputAction action = static_cast<InputAction>(i);
		InputActionsInfo.emplace(action, InputActionInfo());
	}
}

void PlayerInputAction::SetInputAction(const InputAction Action, const float Value)
{
	InputActionInfo& Info = InputActionsInfo.at(Action);
	
	if (Info.InputType == InputType::Pressed && Info.HasBeenPressed)
		return;

	Info.Value = Value;
	for (const auto& callback : Info.Callbacks)
	{
		callback(Value);
	}

	Info.HasBeenPressed = true;
}

void PlayerInputAction::OnReleased(InputAction Action)
{
	InputActionInfo& Info = InputActionsInfo.at(Action);
	Info.HasBeenPressed = false;
}

float PlayerInputAction::GetInputActionValue(const InputAction Action) const
{
	return InputActionsInfo.at(Action).Value;
}

bool PlayerInputAction::IsInputActionPressed(const InputAction Action) const
{
	return InputActionsInfo.at(Action).Value != 0.f;
}

bool PlayerInputAction::IsInputActionReleased(const InputAction Action) const
{
	return InputActionsInfo.at(Action).Value == 0.f;
}

void PlayerInputAction::BindAction(const InputAction InputAction, const std::function<void(float)>& Func, const InputType InputType)
{
	InputActionsInfo.at(InputAction).Callbacks.push_back(Func);
	InputActionsInfo.at(InputAction).InputType = InputType;
}

InputActionInfo::InputActionInfo(): Value(0.f), InputType(), HasBeenPressed(false)
{
}