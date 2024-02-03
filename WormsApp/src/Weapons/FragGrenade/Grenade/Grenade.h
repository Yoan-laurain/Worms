#pragma once

#include <Objects/Prefab/CircleObject.h>

class GrenadeFragment : public SCircleObject
{
public:
	GrenadeFragment();
	~GrenadeFragment();

	/* SActor IMPLEMENTATION */
	virtual void OnCollide(Manifold& contact) override;
	/* SActor IMPLEMENTATION */

	std::function<void()> OnFragmentDestroyCallback;

};

class Grenade : public SCircleObject
{
	public :
		Grenade();
		~Grenade();

		/* SActor IMPLEMENTATION */
		virtual void OnCollide(Manifold& contact) override;
		/* SActor IMPLEMENTATION */

		void OnFragmentDestroy();

		int NumberOfFragmentsToSpawn = 3;
		int NumberOfFragmentsRemaining = 3;
		bool bIsExploded = false;
		std::vector<GrenadeFragment*> fragments;
};