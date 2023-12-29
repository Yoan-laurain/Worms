#pragma once

#include "Objects/SActor.h"

class SPOON_API SCircleObject : public SActor
{
public:
	SCircleObject();
	~SCircleObject();

	void SetRadius(const float radius);
	float GetRadius() const;

	void SetColor(const FColor& color);
	const FColor& GetColor() const;

	class SCircleComponent* GetCircleComponent() const { return CircleComponent; };

	virtual bool IsInBound(const FVector2D& _loc) const override;

protected:

	virtual bool OnMouseEvent(class MouseMovedEvent& _event);

private:

	class SCircleComponent* CircleComponent;

};