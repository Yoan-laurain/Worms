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
	PlayerInputAction(unsigned playerIndex);

	void SetInputAction(InputAction action, float value);
	void OnReleased(InputAction action);

	float GetInputActionValue(InputAction action) const;

	bool IsInputActionPressed(InputAction action) const;
	bool IsInputActionReleased(InputAction action) const;

	void BindAction(InputAction inputAction, std::function<void(float)> func, InputType inputType);

	std::map<InputAction, InputActionInfo> InputActionsInfo;

private:
	unsigned PlayerIndex;

};