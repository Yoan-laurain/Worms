#pragma once

#include <vector>

class ITurnObserver;

class TurnManager
{

    public:
        TurnManager();
        ~TurnManager();

        void registerObserver(ITurnObserver* observer);
        void unregisterObserver(ITurnObserver* observer);
        void nextTurn();

    private:
        void notifyObservers();
    
        int currentPlayer;
        std::vector<ITurnObserver*> observers;
};