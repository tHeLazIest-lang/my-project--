#pragma once
#include "spaceship.hpp"
#include"obstacle.hpp"
#include "alien.hpp"
#include"mysteryship.hpp"
class Game{
   public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        bool run;
        int lives;
        int score;

   private:
        void deleteInactiveLasers();
        Spaceship spaceship;
        std:: vector<Obstacle> CreateObstacles();
        std:: vector<Alien> CreateAliens();
        void MoveAliens();
        void MoveDownAliens(int distance); 
        void AlienShotLaser();
        void CheckForCollisions();
        void GameOver();
        void Reset();
        void InitGame();
        std:: vector<Obstacle> obstacles;
        std:: vector<Alien> aliens;
        std:: vector<Laser> alienLaser;
        int aliensDirection;
        constexpr static float alienLaserShootInterval = 0.35;
        float timeLastAlienFired;
        MysteryShip mysteryship;
        float mysteryShipSpawnInterval;
        float timeLastSpawn; 
            

};