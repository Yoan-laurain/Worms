#pragma once

#include <Spoon/Objects/Prefab/CircleObject.h>

class Bullet : public SCircleObject
{
public:
	Bullet();
	~Bullet() override;

	/* SActor IMPLEMENTATION */
	void OnCollide(SObject* Actor) override;
	/* SActor IMPLEMENTATION */
};