#pragma once

#include <Spoon/Objects/Prefab/CircleObject.h>
#include <Library/Manifold.h>

class Bullet : public SCircleObject
{
public:
	Bullet() = default;
	~Bullet() override;

	/* SActor IMPLEMENTATION */
	void OnCollide(Manifold& Contact) override;
	/* SActor IMPLEMENTATION */
};