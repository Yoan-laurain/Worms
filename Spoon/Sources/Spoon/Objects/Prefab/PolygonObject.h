#pragma once

#include "Objects/SActor.h"

class SPolygonComponent;

class SPOON_API SPolygonObject : public SActor
{
	public : 
		SPolygonObject();
		virtual ~SPolygonObject() override;

		SPolygonComponent* GetPolygonComponent() const { return PolygonComponent; };

		virtual bool IsInBound(const FVector2D& _loc) override;
		virtual void Move(const FVector2D& loc) override;
		virtual void AddForce(const FVector2D& force) override;
		virtual void Tick(float DeltaTime) override;
		virtual float CalculateRotationInertia() override;

		std::vector<FVector2D> GetVertices();

		bool bUpdateVerticesRequired;

	private:
		
		SPolygonComponent* PolygonComponent;
		std::vector<FVector2D> Vertices;
};