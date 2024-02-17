#pragma once

#include <vector>

class ITurnObserver;

class TurnManager
{

    public:
        TurnManager();
        ~TurnManager();

        void RegisterObserver(ITurnObserver* Observer);
        void UnregisterObserver(ITurnObserver* Observer);
    
        void NextTurn();
        void OnEndGame();
    
        bool IsMyTurn(int PlayerId);

        int CurrentPlayer;

    private:
        void NotifyObservers();
    
        std::vector<ITurnObserver*> Observers;
};