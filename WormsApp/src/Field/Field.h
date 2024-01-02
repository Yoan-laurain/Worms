#pragma once

#include "Objects/SActor.h"

class FieldPoint : public SActor 
{
public:
	FieldPoint();

protected:
	void OnCollide(SActor* pActor);
	class SCircleComponent* ShapeComponent;
};

class Field : public SActor
{
public:

	Field();

	void GenerateFieldCurve();

	FTransform GetTransformAt(float percent);

	FTransform& GetSpawnPoint();

	void AddSpawnPoint(const FTransform& spawnPoint);

private:
	std::vector<FieldPoint*> m_FieldPoint;
	class SConvexComponent* CurrentShape;
	std::vector<FTransform> m_SpawnPoints;
};