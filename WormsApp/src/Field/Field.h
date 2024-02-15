#pragma once

#include <Objects/Prefab/PolygonObject.h>

class Field : public SPolygonObject
{
	public:

		Field();
		~Field() override = default;

		void GenerateField();
	
		void CreateSpawnPoints();
		FTransform GetSpawnPoint();

	private:

		std::vector<FTransform> SpawnPoints;
};