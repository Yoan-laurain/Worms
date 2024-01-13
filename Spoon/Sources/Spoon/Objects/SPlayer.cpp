#include "Objects/SPlayer.h"
#include "Core/Application.h"

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

void SPlayer::BindFunctionToInputAction(InputAction inputAction, std::function<void(float)> func)
{
	Application::Get().BindAction(this, inputAction, func);
}