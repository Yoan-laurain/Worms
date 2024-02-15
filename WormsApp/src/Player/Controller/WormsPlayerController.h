#pragma once

#include <Library/TVector.h>

class WormsPlayer;

class WormsPlayerController
{
    public:

        WormsPlayerController();
        
        /* Inputs */
        void ApplyBinding();
        void MoveVertical(float Value, float Sign);
        void MoveHorizontal(float Value, float Sign);
        void Shoot();
        void Reload();
        /* End Inputs */

        void UpdateSpriteDirection(FVector2D& Direction);
        bool CanPerformAction() const;

        WormsPlayer* Player;
        float PlayerSpeed;
};
