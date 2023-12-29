#pragma once

#include "Objects/SActor.h"
#include "Inputs/InputAction.h"

class SPOON_API SPlayer : public SActor
{
	GENERATE()

public:
	SPlayer();
	virtual ~SPlayer();

protected:

	virtual void Tick(float DeltaTime) override;

	void BindFunctionToInputAction(InputAction inputAction, std::function<void(float)> func);

private:

	class SGravityComponent* GravityComponent;
	
	class CircleShape* CollisionComponent;

};
