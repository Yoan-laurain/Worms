#pragma once

#include <vector>
#include <memory>

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
        int currentPlayer;
        std::vector<ITurnObserver*> observers;

        void notifyObservers();
};