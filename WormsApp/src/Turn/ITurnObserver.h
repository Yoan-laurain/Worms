#pragma once

/*
* Toute classe qui veut �tre notifi�e d'un changement de tour doit impl�menter cette interface
*/
class ITurnObserver 
{
    public:
    
    ITurnObserver() = default;
    virtual ~ITurnObserver() = default;
    ITurnObserver(const ITurnObserver& Other) = delete;
    ITurnObserver(ITurnObserver&& Other) = delete;
    ITurnObserver& operator=(const ITurnObserver& Other) = delete;
    ITurnObserver& operator=(ITurnObserver&& Other) = delete;
    
    virtual void OnTurnChange(int CurrentPlayer) = 0;
};