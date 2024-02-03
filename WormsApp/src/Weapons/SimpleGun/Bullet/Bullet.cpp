
#include "Bullet.h"
#include <Spoon/Core/Level.h>
#include "../../WormsApp/src/Player/WormsPlayer.h"
#include "../../../Levels/WormLevel.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
	OnDestroy();
}

void Bullet::OnCollide(Manifold& contact)
{
	MarkActorToDestruction();

	if (contact.BodyA)
	{
		WormsPlayer* player = dynamic_cast<WormsPlayer*>(contact.BodyA);
		if (player && contact.BodyB)
		{
			player->GetWeaponStrategy()->DoDamage(player);
		}
	}
}

void Bullet::OnDestroy()
{
	WormLevel* level = dynamic_cast<WormLevel*>(GetWorld());
	level->m_TurnManager->nextTurn();
}
