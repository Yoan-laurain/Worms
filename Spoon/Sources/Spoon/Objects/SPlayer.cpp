#include "Objects/SPlayer.h"
#include "Core/Application.h"
#include "Inputs/Enums/InputAction.h"

SPlayer::SPlayer()
{
	Application::Get().AddNewPlayer(this);
}

void SPlayer::Tick(float DeltaTime)
{
	SPolygonObject::Tick(DeltaTime);
}

// TODO : Move this in a PlayerController class
void SPlayer::BindFunctionToInputAction(const InputAction InputAction, const std::function<void(float)>& Func , const InputType InputType)
{
	Application::Get().BindAction(this, InputAction, Func, InputType);
}