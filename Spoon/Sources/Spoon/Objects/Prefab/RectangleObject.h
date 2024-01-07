#pragma once

#include "Objects/SActor.h"

class SPOON_API SRectangleObject : public SActor
{

	public : 
		SRectangleObject();
		virtual ~SRectangleObject();

		std::vector<FVector2D> GetVertices();

		class SRectangleComponent* GetRectangleComponent() const { return RectangleComponent; };

		virtual bool IsInBound(const FVector2D& _loc) override;

	private : 
		class SRectangleComponent* RectangleComponent;
		std::vector<FVector2D> vertices;
};