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

        int currentPlayer;

    private:
        void notifyObservers();
    
        std::vector<ITurnObserver*> observers;
};