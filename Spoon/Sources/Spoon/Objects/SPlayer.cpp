#include "Objects/SPlayer.h"
#include "Core/Application.h"
#include "Inputs/InputAction.h"

SPlayer::SPlayer()
{
	Application::Get().AddNewPlayer(this);
}

SPlayer::~SPlayer()
{
}

void SPlayer::Tick(float DeltaTime)
{
	SPolygonObject::Tick(DeltaTime);
}

// TODO : Move this in a PlayerController class
void SPlayer::BindFunctionToInputAction(InputAction inputAction, std::function<void(float)> func , InputType inputType)
{
	Application::Get().BindAction(this, inputAction, func, inputType);
}