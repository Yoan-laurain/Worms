#pragma once

#include "Objects/Prefab/RectangleObject.h"
#include <Inputs/PlayerInputAction.h>

enum class InputAction;

class SPOON_API SPlayer : public SRectangleObject
{
	GENERATE()

public:
	SPlayer();
	virtual ~SPlayer() override;
	
protected:

	virtual void Tick(float DeltaTime) override;
	
	void BindFunctionToInputAction(InputAction inputAction, std::function<void(float)> func, InputType inputType);
};