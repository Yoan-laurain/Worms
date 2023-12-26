#pragma once

/*
* Toute classe qui veut �tre notifi�e d'un changement de tour doit impl�menter cette interface
*/
class ITurnObserver 
{
    public:
    
    virtual ~ITurnObserver() = default;
    ITurnObserver() = default;
    ITurnObserver(const ITurnObserver& other) = default;
    ITurnObserver& operator=(const ITurnObserver& other) = default;
    ITurnObserver(ITurnObserver&& other) = default;
    ITurnObserver& operator=(ITurnObserver&& other) = default;
    
    virtual void onTurnChange(int currentPlayer) = 0;
};