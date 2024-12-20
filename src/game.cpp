#include "game.hpp"
#include<iostream>

Game::Game()
{ 
    InitGame();
}

Game::~Game()
{
    Alien::UnloadImages();
}

void Game::Update(){
    if(run){
        double currentTime = GetTime();
        if(currentTime - timeLastSpawn > mysteryShipSpawnInterval) {
            mysteryship.Spawn();
            timeLastSpawn = GetTime();
            mysteryShipSpawnInterval = GetRandomValue(10, 20);
        }
        for(auto& laser: spaceship.lasers){
            laser.Update();
        }
        MoveAliens();
        AlienShotLaser();
        for(auto& laser: alienLaser) {
                laser.Update();
        }
        deleteInactiveLasers();
        mysteryship.Update();
        CheckForCollisions();
    } else{
        if(IsKeyDown(KEY_ENTER)){
            Reset();
            InitGame();
        }
    }

}

void Game::Draw(){
    spaceship.Draw();

    for(auto& laser: spaceship.lasers){
        laser.Draw();
    }
    for(auto& obstacle: obstacles) {
        obstacle.Draw();
    }
    for(auto& alien: aliens){
        alien.Draw();
    }
    for(auto& laser: alienLaser) {
        laser.Draw();
    }
    mysteryship.Draw();


}

void Game::HandleInput(){
    if(run){
        if(IsKeyDown(KEY_LEFT)){
            spaceship.Movedleft();
        }
        else if(IsKeyDown(KEY_RIGHT)){
            spaceship.Moveright();
        }
        else if(IsKeyDown(KEY_SPACE)){
            spaceship.Firelaser();
        }
    }
}

void Game::deleteInactiveLasers()
{

    for(auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();){
        if(!it->active){
            it = spaceship.lasers.erase(it);
        }
        else {
            ++it;
        }
    }
        for(auto it = alienLaser.begin(); it != alienLaser.end();){
        if(!it -> active) {
            it = alienLaser.erase(it);
        } else {
            ++ it;
        }
    }
}



std::vector<Obstacle> Game::CreateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size() * 4;
    float gap = (GetScreenWidth() - (4 * obstacleWidth))/5;

    for(int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));
    }
    return obstacles;
    
}

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens;
    for(int row = 0; row < 5; row++) {
        for(int column = 0; column < 11; column++) {

            int alienType;
            if(row == 0) {
                alienType = 3;
            } else if (row == 1 || row == 2) {
                alienType = 2;
            } else {
                alienType = 1;
            }

            float x = 75 + column * 55;
            float y = 110 + row * 55;
            aliens.push_back(Alien(alienType, {x, y}));
        }
    }
    return aliens;
}

void Game::MoveAliens()
{
    for(auto& alien: aliens) {
        if(alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25) {
            aliensDirection = -1;
            MoveDownAliens(3);
        }
        if(alien.position.x < 25) {
            aliensDirection = 1;
            MoveDownAliens(3);
        }

        alien.Update(aliensDirection);
    }
}

void Game::MoveDownAliens(int distance)
{
    for(auto& alien: aliens) {
        alien.position.y += distance;
    }
}

void Game::AlienShotLaser()
{
     double currentTime = GetTime();
    if(currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()) {
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = aliens[randomIndex];
        alienLaser.push_back(Laser({alien.position.x + alien.alienImages[alien.type -1].width/2, 
                                    alien.position.y + alien.alienImages[alien.type - 1].height}, 6));
        timeLastAlienFired = GetTime();
    }
}

void Game::CheckForCollisions()
{
    //Spaceship Lasers

    for(auto& laser: spaceship.lasers) {
        auto it = aliens.begin();
        while(it != aliens.end()){
            if(CheckCollisionRecs(it -> getRect(), laser.getRect()))
            {
                if (it->type==1){
                    score+=100;
                }else if(it->type==2){
                    score+=200;
                }
                else{
                    score+=300;
                }
                it = aliens.erase(it);
                laser.active = false;
            } else {
                ++it;
            }
        }

        for(auto& obstacle: obstacles){
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()){
                if(CheckCollisionRecs(it -> getRect(), laser.getRect())){
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }

        if(CheckCollisionRecs(mysteryship.getRect(), laser.getRect())){
            mysteryship.alive = false;
            laser.active = false;
            score+=500;

        }
    }

        //Alien Lasers

    for(auto& laser: alienLaser) {
        if(CheckCollisionRecs(laser.getRect(), spaceship.getRect())){
            laser.active = false;
            
            lives--;
            if(lives == 0){
                GameOver();
            }
           
        }

          for(auto& obstacle: obstacles){
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()){
                if(CheckCollisionRecs(it -> getRect(), laser.getRect())){
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }

            //Alien Collision with Obstacle
    
    for(auto& alien: aliens) {
        for(auto& obstacle: obstacles) {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()) {
                if(CheckCollisionRecs(it -> getRect(), alien.getRect())) {
                    it = obstacle.blocks.erase(it);
                } else {
                    it ++;
                }
            }
        }

        if(CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
           GameOver();
        }
    }
}
}

void Game::GameOver()
{
    run = false;
}

void Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    alienLaser.clear();
    obstacles.clear();
}

void Game::InitGame()
{
    obstacles = CreateObstacles();
    aliens  = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0;
    timeLastSpawn = 0.0;
    mysteryShipSpawnInterval = GetRandomValue(8, 16);
    lives = 3;
    score=0;
    run = true;
}


