#include "Objects/SPlayer.h"
#include "Core/Application.h"
#include "Components/SCollisionComponent.h"

SPlayer::SPlayer() : SPolygonObject()
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