#pragma once

#include "Objects/Prefab/PolygonObject.h"

class Field : public SPolygonObject
{
public:

	Field();

	void GenerateFieldCurve();

	FTransform& GetSpawnPoint();

private:

	std::vector<FTransform> m_SpawnPoints;
	
	void AddSpawnPoint(const FTransform& spawnPoint);
};