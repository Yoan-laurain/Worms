#include "SMovementComponent.h"
#include "Objects/SActor.h"
#include "Core/Level.h"
#include "snpch.h"

SMovementComponent::SMovementComponent(SActor* owner) 
	: SComponent(owner),
	Velocity(FVector2D::Zero()),
	Acceleration(FVector2D::Zero()),
	GravityScale(1.f),
	m_MovementMode(EObjectMovement::Move_None),
	PendingForce(FVector2D::Zero()),
	PendingImpulse(FVector2D::Zero())
{
}

float SMovementComponent::GetGravityZ() const
{
	return GetOwner()->GetWorld()->GetGravityZ() * GravityScale;
}

void SMovementComponent::OnUpdate(const float Deltatime)
{
	UpdatePhys(Deltatime);
	UpdateMovement(Deltatime);
}

void SMovementComponent::UpdatePhys(const float Deltatime)
{
	if (IsMovementMode(EObjectMovement::Move_Falling))
	{
		FallingPhys(Deltatime);
	}
}

void SMovementComponent::UpdateMovement(const float Deltatime)
{
}

void SMovementComponent::ApplyPendingForce()
{
}

void SMovementComponent::FallingPhys(const float Deltatime)
{
	// Todo faire en sorte que le joueur tombe ici.
}

FVector2D SMovementComponent::CalcFallingVelocity(const FVector2D& currentVelocity, const FVector2D& currentAcceleration, const float Deltatime)
{
	return FVector2D();
}

bool SMovementComponent::IsMovementMode(const EObjectMovement& move) const
{
	return move == m_MovementMode;
}

void SMovementComponent::SafeMoveOwner(const FVector2D target, const float rotation, bool bShouldCollide)
{
	GetOwner()->Move(target);
	GetOwner()->
}
