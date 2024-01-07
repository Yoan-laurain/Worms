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

	FTransform GetTransformAt(const float percent);

	FTransform& GetSpawnPoint();

private:
	void AddSpawnPoint(const FTransform& spawnPoint);

	std::vector<FTransform> m_SpawnPoints;
	std::vector<FieldPoint*> m_FieldPoint;

	class SShapeComponent* ShapeComponent;

};