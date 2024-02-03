#pragma once

#include <Spoon/Objects/Prefab/CircleObject.h>
#include <Library/Manifold.h>

class Bullet : public SCircleObject
{
public:
	Bullet();
	virtual ~Bullet() override;

	/* SActor IMPLEMENTATION */
	virtual void OnCollide(Manifold& contact) override;
	/* SActor IMPLEMENTATION */
};
