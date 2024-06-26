﻿#include "WormsPlayerController.h"
#include "../../Widgets/Player/PlayerWidget.h"
#include "../../Config.h"
#include "../WormsPlayer.h"
#include <Objects/Prefab/PolygonObject.h>
#include <Inputs/Enums/InputAction.h>
#include <Inputs/Enums/InputType.h>
#include <Library/TStruct.h>
#include <Objects/Components/SShapeComponent.h>

WormsPlayerController::WormsPlayerController() 
    : Player(nullptr)
    , PlayerSpeed(10.f)
    , ForwardVector(FVector2D::Right())
{
}

void WormsPlayerController::ApplyBinding()
{
    if (Player)
    {
        Player->BindFunctionToInputAction(InputAction::Left, std::bind(&WormsPlayerController::MoveHorizontal, this, std::placeholders::_1, -1.f),InputType::Hold);
        Player->BindFunctionToInputAction(InputAction::Right, std::bind(&WormsPlayerController::MoveHorizontal, this, std::placeholders::_1, 1.f), InputType::Hold);

        Player->BindFunctionToInputAction(InputAction::Up, std::bind(&WormsPlayerController::MoveVertical, this, std::placeholders::_1, -1.f), InputType::Hold);
        Player->BindFunctionToInputAction(InputAction::Down, std::bind(&WormsPlayerController::MoveVertical, this, std::placeholders::_1, 1.f), InputType::Hold);

        Player->BindFunctionToInputAction(InputAction::Fire, std::bind(&WormsPlayerController::Shoot, this), InputType::Pressed);
        Player->BindFunctionToInputAction(InputAction::Reload, std::bind(&WormsPlayerController::Reload, this), InputType::Pressed);
    }
}

void WormsPlayerController::Shoot()
{
    if (!CanPerformAction())
        return;
    
    FVector2D Location = Player->GetLocation();
    Location.X += ForwardVector.X * 2.5f * Player->GetSize().X;

    FTransform ShootingPoint(Location, FVector2D(0.f), 0.f);

    if (Player->WeaponStrategy->Shoot(*Player->GetWorld(), ShootingPoint, ForwardVector))
    {
        Player->bHasShot = true;
        Player->MyPlayerWidget->UpdateAmountOfAmmo();
        Player->MyPlayerWidget->StopTimer();
    }
}

void WormsPlayerController::Reload()
{
    if (!CanPerformAction())
        return;

    Player->WeaponStrategy->Reload(); 
    Player->MyPlayerWidget->UpdateAmountOfAmmo(); 
}

void WormsPlayerController::MoveVertical(float Value, float Sign)
{
    if (!CanPerformAction())
        return;

    if (Value > 0.f)
    {	
        FVector2D Direction = FVector2D( 0.f, Sign * Value);

        Player->AddForce(Direction * Value * PlayerSpeed);
    }
}

void WormsPlayerController::MoveHorizontal(float Value, float Sign)
{
    if (!CanPerformAction())
        return;

    if (Value > 0.f)
    {	
        FVector2D Direction = FVector2D(Sign * Value, 0.f);
        ForwardVector = Direction;
        Player->AddForce(Direction * Value * PlayerSpeed);

        UpdateSpriteDirection(Direction);
    }
}

void WormsPlayerController::UpdateSpriteDirection(FVector2D& Direction)
{
    if (Direction.X > 0)
    {
        Player->GetPolygonComponent()->TexturePath = Player->PlayerId == 0 ? Config::Player1Right : Config::Player2Right;
        return;
    }
    
    Player->GetPolygonComponent()->TexturePath = Player->PlayerId == 0 ?  Config::Player1Left : Config::Player2Left;
}

bool WormsPlayerController::CanPerformAction() const
{
    return Player && Player->IsMyTurn() && !Player->bHasShot;
}