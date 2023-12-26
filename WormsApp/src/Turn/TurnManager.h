#pragma once

#include <vector>
#include <memory>

class ITurnObserver;

class TurnManager
{

    public:
        TurnManager();
        ~TurnManager();

        void registerObserver(std::shared_ptr<ITurnObserver> observer);
        void unregisterObserver(std::shared_ptr<ITurnObserver> observer);
        void nextTurn();

    private:
        int currentPlayer;
        std::vector<std::weak_ptr<ITurnObserver>> observers;

        void notifyObservers();
};