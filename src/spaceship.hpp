#pragma once
#include<raylib.h>
#include"laser.hpp"
#include<vector>

class Spaceship{
    
    public:
        Spaceship();
        ~Spaceship();
        void Draw();
        void Movedleft();
        void Moveright();
        void Firelaser();
        Rectangle getRect();
        void Reset();
        std::vector<Laser>lasers;


    private:
        Texture2D image;
        Vector2 position;
        double lastFireTime;

};