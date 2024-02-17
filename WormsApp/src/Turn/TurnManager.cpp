#include "TurnManager.h"
#include "ITurnObserver.h"
#include <iostream>

TurnManager::TurnManager() : CurrentPlayer(1)
{
}

TurnManager::~TurnManager()
{
    for (const auto& WeakObserver : Observers)
    {
		auto Observer = WeakObserver;
        if (Observer)
        {
			UnregisterObserver(Observer);
		}
	}
}

void TurnManager::RegisterObserver(ITurnObserver* Observer)
{
    Observers.push_back(Observer);
}

void TurnManager::UnregisterObserver(ITurnObserver* Observer)
{
    auto it = std::find(Observers.begin(), Observers.end(), Observer);
    if (it != Observers.end())
    {
        Observers.erase(it, Observers.end());
    }
}

void TurnManager::NextTurn()
{
    CurrentPlayer = CurrentPlayer == 1 ? 0 : 1;
    NotifyObservers();
}

void TurnManager::OnEndGame()
{
    //TODO : Handle end game correctly
    std::cout << "Game over" << std::endl;
    
    exit(0);
}

bool TurnManager::IsMyTurn(int PlayerId)
{
    return CurrentPlayer == PlayerId;
}

void TurnManager::NotifyObservers()
{
    for (const auto& WeakObserver : Observers)
    {
        auto Observer = WeakObserver;
        if (Observer)
        {
            Observer->OnTurnChange(CurrentPlayer);
        }
    }
}