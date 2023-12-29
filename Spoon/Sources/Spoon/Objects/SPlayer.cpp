#include "Objects/SPlayer.h"
#include "Core/Application.h"
#include "Components/SGravityComponent.h"

Player::Player() : SActor()
{
	Application::Get().AddNewPlayer(this);
	GravityComponent = CreateComponent<SGravityComponent>("Gravity Component");
	std::cout << GetClassId() << std::endl;
}

Player::~Player()
{
}

void Player::Tick(float DeltaTime)
{
	SActor::Tick(DeltaTime);
}

void Player::BindFunctionToInputAction(InputAction inputAction, std::function<void(float)> func)
{
	Application::Get().BindAction(this, inputAction, func);
}