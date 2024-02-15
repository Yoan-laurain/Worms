#pragma once

namespace Config {

    constexpr int WindowWidth = 1280;
    constexpr int WindowHeight = 720;

    constexpr int MaxPlayers = 2;
    constexpr int TimerForATurn = 15;
    
    constexpr float SectionForOnePlayer = WindowWidth / MaxPlayers;
    constexpr float CenterOfSection = SectionForOnePlayer / 2.f;
    
    constexpr int PlayerSize = 25;

    inline std::string Player1Right = "Ressources/WormsPlayerRight.png";
    inline std::string Player2Right = "Ressources/WormsPlayer2Right.png";
    inline std::string Player1Left = "Ressources/WormsPlayerLeft.png";
    inline std::string Player2Left = "Ressources/WormsPlayer2Left.png";
    
    inline std::string SimpleGun = "Ressources/SimpleGun.png";
    inline std::string GrenadeLauncher = "Ressources/GrenadeLauncher.png";
    inline std::string Graviton = "Ressources/Graviton.png";
    inline std::string Wind = "Ressources/Wind.png";
    inline std::string WindDirection = "Ressources/WindDirection.png";
    inline std::string Bullet = "Ressources/Saw.png";
    inline std::string Grenade = "Ressources/Grenade.png";
    inline std::string GrenadePieces = "Ressources/GrenadePieces.png";
}