#include "Player.h"
#include "Application.h"
#include "Object/Component/SGravityComponent.h"

Player::Player() : SActor()
{
	Application::Get().AddNewPlayer(this);
	GravityComponent = CreateComponent<SGravityComponent>();
}

Player::~Player()
{
}

void Player::Tick(float DeltaTime)
{
	SActor::Tick(DeltaTime);
	if (GravityComponent)
	{
		GravityComponent->Simulated(!bIsPressed);
	}
}

void Player::BindFunctionToInputAction(InputAction inputAction, std::function<void(float)> func)
{
	Application::Get().BindAction(this, inputAction, func);
}