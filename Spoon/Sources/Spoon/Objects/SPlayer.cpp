#include "Objects/SPlayer.h"
#include "Core/Application.h"
#include "Components/SGravityComponent.h"
#include "Components/SCollisionComponent.h"

SPlayer::SPlayer() : SActor()
{
	Application::Get().AddNewPlayer(this);
	GravityComponent = CreateComponent<SGravityComponent>("Gravity Component");
	CollisionComponent = CreateComponent<CircleShape>("Collision Component");
	CollisionComponent->Radius = 50;
}

SPlayer::~SPlayer()
{
}

void SPlayer::Tick(float DeltaTime)
{
	SActor::Tick(DeltaTime);
}

void SPlayer::BindFunctionToInputAction(InputAction inputAction, std::function<void(float)> func)
{
	Application::Get().BindAction(this, inputAction, func);
}