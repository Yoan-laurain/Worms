#pragma once

#include <map>

#include <functional>
#include <vector>

enum class InputAction;

class PlayerInputAction final
{
public:
	PlayerInputAction(unsigned playerIndex);

	void SetInputAction(InputAction action, float value);

	float GetInputActionValue(InputAction action) const;

	bool IsInputActionPressed(InputAction action) const;
	bool IsInputActionReleased(InputAction action) const;

	void BindAction(InputAction inputAction, std::function<void(float)> func);

private:
	unsigned PlayerIndex;

	struct InputActionInfo
	{
		InputActionInfo();

		float Value;
		std::vector<std::function<void(float)>> Callbacks;
	};

	std::map<InputAction, InputActionInfo> InputActionsInfo;
};