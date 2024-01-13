#pragma once

#include "Objects/SActor.h"

class SCircleComponent;

class SPOON_API SCircleObject : public SActor
{
public:
	SCircleObject();
	virtual ~SCircleObject() override;

	void SetRadius(float radius);
	float GetRadius() const;

	void SetColor(const FColor& color);
	const FColor& GetColor() const;

	SCircleComponent* GetCircleComponent() const { return CircleComponent; };
	
	/* SActor IMPLEMENTATION */
	virtual bool IsInBound(const FVector2D& _loc) override;
	virtual float CalculateRotationInertia() override;
	virtual void SetTransform(const FTransform& transform) override;
	/* END SActor IMPLEMENTATION */
	
private:
	SCircleComponent* CircleComponent;
};