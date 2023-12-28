#pragma once

#include "Object/SActor.h"
#include "Spoon/Input/InputAction.h"

class SPOON_API Player : public SActor
{
public:
	Player();
	virtual ~Player();

protected:

	virtual void Tick(float DeltaTime) override;

	void BindFunctionToInputAction(InputAction inputAction, std::function<void(float)> func);

private:

	class SGravityComponent* GravityComponent;

};
