#include "TurnManager.h"
#include "ITurnObserver.h"
#include <iostream>

TurnManager::TurnManager() : currentPlayer(1)
{
}

TurnManager::~TurnManager()
{
    for (const auto& weakObserver : observers)
    {
		auto observer = weakObserver;
        if (observer)
        {
			unregisterObserver(observer);
		}
	}
}

void TurnManager::registerObserver(ITurnObserver* observer)
{
    observers.push_back(observer);
}

void TurnManager::unregisterObserver(ITurnObserver* observer)
{
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end())
    {
        observers.erase(it, observers.end());
    }
}

void TurnManager::nextTurn()
{
    currentPlayer = currentPlayer == 1 ? 0 : 1;
    notifyObservers();
}

void TurnManager::notifyObservers()
{
    for (const auto& weakObserver : observers)
    {
        auto observer = weakObserver;
        if (observer)
        {
            observer->onTurnChange(currentPlayer);
        }
    }
}