#pragma once

#include "PolygonObject.h"

class SPOON_API SRectangleObject : public SPolygonObject
{
	public : 

		SRectangleObject();
	
		/* SActor IMPLEMENTATION */
		virtual void SetTransform(const FTransform& transform) override;
		virtual void AddRotation(const float addRotation) override;
		/* END SActor IMPLEMENTATION */
};