#pragma once

#include "Objects/SActor.h"

class SPOON_API SPolygonObject : public SActor
{
	public : 
		SPolygonObject();
		virtual ~SPolygonObject();

		class SPolygonComponent* GetPolygonComponent() const { return PolygonComponent; };

		virtual bool IsInBound(const FVector2D& _loc) override;

		std::vector<FVector2D> GetVertices();

	private:
		
		class SPolygonComponent* PolygonComponent;
		std::vector<FVector2D> Vertices;
};