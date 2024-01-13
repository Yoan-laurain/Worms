#pragma once

#include "Objects/Prefab/PolygonObject.h"

enum class InputAction;

class SPOON_API SPlayer : public SPolygonObject
{
	GENERATE()

public:
	SPlayer();
	virtual ~SPlayer() override;
	
protected:

	virtual void Tick(float DeltaTime) override;
	
	void BindFunctionToInputAction(InputAction inputAction, std::function<void(float)> func);
};