#include "Bullet.h"
#include "../../WormsApp/src/Player/WormsPlayer.h"
#include "../../../Levels/WormLevel.h"
#include <Spoon/Core/Level.h>

Bullet::~Bullet()
{
	WormLevel* Level = dynamic_cast<WormLevel*>(GetWorld());

	if (Level)
	{
		Level->ATurnManager->NextTurn();
	}
}

void Bullet::OnCollide(SObject* Actor)
{
	MarkActorToDestruction();

	WormsPlayer* Player = dynamic_cast<WormsPlayer*>(Actor);
	if (Player)
	{
		Player->WeaponStrategy->DoDamage(Player);
	}
}