#pragma once

#include "Object/SActor.h"
#include "Spoon/Input/InputAction.h"

class SPOON_API Player : public SActor
{
public:
	Player();
	~Player() override;

protected:
	void BindFunctionToInputAction(InputAction inputAction, std::function<void(float)> func);
};
