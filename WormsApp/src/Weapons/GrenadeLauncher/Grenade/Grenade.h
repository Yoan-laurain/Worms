#pragma once

#include <Objects/Prefab/CircleObject.h>

class GrenadeFragment : public SCircleObject
{
public:
	GrenadeFragment() = default;
	~GrenadeFragment() override;

	/* SActor IMPLEMENTATION */
	void OnCollide(SObject* Actor) override;
	/* SActor IMPLEMENTATION */

	std::function<void()> OnFragmentDestroyCallback;

};

// TODO : Re design the grenade mechanics
class Grenade : public SCircleObject
{
	public :
		Grenade();
		~Grenade() override;
	
		void SpawnFragment(int FragmentIndex);

		/* SActor IMPLEMENTATION */
		void OnCollide(SObject* Actor) override;
		/* SActor IMPLEMENTATION */

		void OnFragmentDestroy();

		int NumberOfFragmentsToSpawn = 3;
		int NumberOfFragmentsRemaining = 3;
	
		bool bIsExploded = false;
	
		std::vector<GrenadeFragment*> Fragments;
};