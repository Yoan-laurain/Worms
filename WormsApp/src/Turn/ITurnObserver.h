#pragma once

/*
* Toute classe qui veut �tre notifi�e d'un changement de tour doit impl�menter cette interface
*/
class ITurnObserver 
{
    public:
    
    ITurnObserver() = default;
    virtual ~ITurnObserver() = default;
    ITurnObserver(const ITurnObserver& other) = delete;
    ITurnObserver(ITurnObserver&& other) = delete;
    ITurnObserver& operator=(const ITurnObserver& other) = delete;
    ITurnObserver& operator=(ITurnObserver&& other) = delete;
    
    virtual void onTurnChange(int currentPlayer) = 0;
};