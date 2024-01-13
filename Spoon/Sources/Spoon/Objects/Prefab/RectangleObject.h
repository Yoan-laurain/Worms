#pragma once

#include "PolygonObject.h"

class SPOON_API SRectangleObject : public SPolygonObject
{
	public : 

		SRectangleObject();
	
		/* SActor IMPLEMENTATION */
		virtual void SetTransform(const FTransform& transform) override;
		/* END SActor IMPLEMENTATION */
};