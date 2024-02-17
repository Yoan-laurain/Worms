#pragma once

#include "Objects/Prefab/RectangleObject.h"

enum class InputAction;
enum class InputType;

class SPOON_API SPlayer : public SRectangleObject
{
	GENERATE()

public:
	SPlayer();
	virtual ~SPlayer() override = default;
	
	void BindFunctionToInputAction(InputAction InputAction, std::function<void(float)> Func, InputType InputType);
	
protected:
	void Tick(float DeltaTime) override;
};