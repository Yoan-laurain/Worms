#include "Player.h"
#include "Application.h"

Player::Player() : SActor()
{
	Application::Get().AddNewPlayer(this);
}

Player::~Player()
{
}

void Player::BindFunctionToInputAction(InputAction inputAction, std::function<void(float)> func)
{
	Application::Get().BindAction(this, inputAction, func);
}