#pragma once

#include "PolygonObject.h"

class SPOON_API SRectangleObject : public SPolygonObject
{
	public : 

		SRectangleObject() = default;
		virtual ~SRectangleObject() override = default;
	
		/* SActor IMPLEMENTATION */
		void SetTransform(const FTransform& transform) override;
		/* END SActor IMPLEMENTATION */
};