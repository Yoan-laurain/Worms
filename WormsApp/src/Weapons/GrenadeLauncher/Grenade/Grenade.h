#pragma once

#include <Objects/Prefab/CircleObject.h>

class GrenadeFragment : public SCircleObject
{
public:
	GrenadeFragment();
	~GrenadeFragment() override;

	/* SActor IMPLEMENTATION */
	void OnCollide(SObject* Actor) override;
	/* SActor IMPLEMENTATION */

	std::function<void()> OnFragmentDestroyCallback;

};

class Grenade : public SCircleObject
{
	public :
		Grenade();
		~Grenade() override = default;
	
		void SpawnFragment(int FragmentIndex);

		/* SActor IMPLEMENTATION */
		void OnCollide(SObject* Actor) override;
		/* SActor IMPLEMENTATION */

		int NumberOfFragmentsToSpawn = 3;
	
		bool bIsExploded = false;
};