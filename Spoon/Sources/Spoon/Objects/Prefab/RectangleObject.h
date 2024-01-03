#pragma once

#include "Objects/SActor.h"

class SPOON_API SRectangleObject : public SActor
{

	public : 
		SRectangleObject();
		~SRectangleObject();

		std::vector<FVector2D> GetVertices();

		class SRectangleComponent* GetRectangleComponent() const { return RectangleComponent; };

		// TODO : Factorize this method
		virtual bool IsInBound(const FVector2D& _loc) override;

	protected :
		// TODO : Factorize this method
		virtual bool OnMouseEvent(class MouseMovedEvent& _event);

	private : 
		class SRectangleComponent* RectangleComponent;
		std::vector<FVector2D> vertices;
};