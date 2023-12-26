#include "TurnManager.h"
#include "ITurnObserver.h"

TurnManager::TurnManager() : currentPlayer(1)
{
}

TurnManager::~TurnManager()
{
    for (const auto& weakObserver : observers)
    {
		auto observer = weakObserver.lock();
        if (observer)
        {
			unregisterObserver(observer);
		}
	}
}

void TurnManager::registerObserver(std::shared_ptr<ITurnObserver> observer)
{
    observers.push_back(observer);
}

void TurnManager::unregisterObserver(std::shared_ptr<ITurnObserver> observer)
{
    auto it = std::remove_if(observers.begin(), observers.end(),
        [observer](const std::weak_ptr<ITurnObserver>& weakObs) {
            return weakObs.lock() == observer;
        });

    observers.erase(it, observers.end());
}

void TurnManager::nextTurn()
{
    currentPlayer = (currentPlayer % 2) + 1;
    notifyObservers();
}

void TurnManager::notifyObservers()
{
    for (const auto& weakObserver : observers)
    {
        auto observer = weakObserver.lock();
        if (observer)
        {
            observer->onTurnChange(currentPlayer);
        }
    }
}