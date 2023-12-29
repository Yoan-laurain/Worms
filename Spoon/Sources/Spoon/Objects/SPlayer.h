#pragma once

#include "Objects/SActor.h"
#include "Inputs/InputAction.h"

class SPOON_API Player : public SActor
{
	GENERATE()

public:
	Player();
	virtual ~Player();

protected:

	virtual void Tick(float DeltaTime) override;

	void BindFunctionToInputAction(InputAction inputAction, std::function<void(float)> func);

private:

	class SGravityComponent* GravityComponent;

};
