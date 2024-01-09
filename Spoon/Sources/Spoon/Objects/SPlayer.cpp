#include "Objects/SPlayer.h"
#include "Core/Application.h"
#include "Components/SGravityComponent.h"
#include "Components/SCollisionComponent.h"

SPlayer::SPlayer() : SPolygonObject()
{
	Application::Get().AddNewPlayer(this);
	GravityComponent = CreateComponent<SGravityComponent>("Gravity Component");

}

SPlayer::~SPlayer()
{
}

void SPlayer::Tick(float DeltaTime)
{
	SPolygonObject::Tick(DeltaTime);
	//GravityComponent->Simulated(true);
}

void SPlayer::BindFunctionToInputAction(InputAction inputAction, std::function<void(float)> func)
{
	Application::Get().BindAction(this, inputAction, func);
}