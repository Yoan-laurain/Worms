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

void Bullet::OnCollide(Manifold& Contact)
{
	MarkActorToDestruction();

	if (Contact.BodyA)
	{
		WormsPlayer* Player = dynamic_cast<WormsPlayer*>(Contact.BodyA);
		if (Player && Contact.BodyB)
		{
			Player->WeaponStrategy->DoDamage(Player);
		}
	}
}