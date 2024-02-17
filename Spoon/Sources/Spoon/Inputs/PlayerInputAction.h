#pragma once

#include <map>
#include <functional>
#include <vector>

enum class InputType;
enum class InputAction;

struct InputActionInfo
{
	InputActionInfo();

	float Value;
	std::vector<std::function<void(float)>> Callbacks;
	InputType InputType;
	bool HasBeenPressed;
};

class PlayerInputAction final
{
public:
	PlayerInputAction();

	void SetInputAction(InputAction Action, float Value);
	void OnReleased(InputAction Action);

	float GetInputActionValue(InputAction Action) const;

	bool IsInputActionPressed(InputAction Action) const;
	bool IsInputActionReleased(InputAction Action) const;

	void BindAction(InputAction InputAction, const std::function<void(float)>& Func, InputType InputType);

	std::map<InputAction, InputActionInfo> InputActionsInfo;
};