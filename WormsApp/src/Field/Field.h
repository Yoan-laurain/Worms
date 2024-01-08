#pragma once

#include "Objects/Prefab/PolygonObject.h"

class Field : public SPolygonObject
{
public:

	Field();

	void GenerateFieldCurve();

	FTransform& GetSpawnPoint();

private:
	void AddSpawnPoint(const FTransform& spawnPoint);

	std::vector<FTransform> m_SpawnPoints;
};