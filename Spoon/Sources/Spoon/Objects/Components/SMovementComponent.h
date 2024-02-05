#pragma once
#include "SComponent.h"
#include "Library/TVector.h"

enum class EObjectMovement
{
	Move_None,
	Move_Walking,
	Move_Falling
};

class SMovementComponent : public SComponent
{
	
public:

	SMovementComponent(class SActor* owner = nullptr);

	virtual float GetGravityZ() const;

protected:

	// Begin SComponent
	virtual void OnUpdate(const float Deltatime) override;
	// End SComponent

	virtual void UpdatePhys(const float Deltatime);
	virtual void UpdateMovement(const float Deltatime);

	void ApplyPendingForce();

	void FallingPhys(const float Deltatime);

	FVector2D CalcFallingVelocity(const FVector2D& currentVelocity, const FVector2D& currentAcceleration, const float Deltatime);

	bool IsMovementMode(const EObjectMovement& move) const;

	void SafeMoveOwner(const FVector2D target, const float rotation, bool bShouldCollide);

protected:

	FVector2D Velocity;

	FVector2D Acceleration;

	float GravityScale;

private:

	EObjectMovement m_MovementMode;

	FVector2D PendingForce;

	FVector2D PendingImpulse;

};

