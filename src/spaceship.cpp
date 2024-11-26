#include "spaceship.hpp"

Spaceship::Spaceship()
{
    image = LoadTexture("Graphics/spaceship2.png");
    position.x =(GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height - 100;
    lastFireTime = 0.0;

}

Spaceship::~Spaceship()
{
    UnloadTexture(image);
}

void Spaceship::Draw(){

    DrawTextureV(image, position, WHITE);
}
void Spaceship::Movedleft(){
    position.x -= 6;
    if(position.x < 25) position.x = 25;
}

void Spaceship::Moveright(){
    position.x += 6;
    if(position.x > GetScreenWidth() - image.width -25) position.x = GetScreenWidth() - image.width -25;
}

void Spaceship::Firelaser()
{
    if(GetTime() - lastFireTime >= 0.25){
        lasers.push_back(Laser({position.x + image.width/2 - 2,position.y},-6));
        lastFireTime = GetTime();
    }
}

Rectangle Spaceship::getRect()
{
    return {position.x, position.y, float(image.width), float(image.height)};
}

void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - image.width)/2.0;
    position.y = GetScreenHeight() - image.height - 100;
    lasers.clear();
}
