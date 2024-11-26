#include<raylib.h>
#include"game.hpp"
#include<string>

std::string FormatWithLeadingZeros(int number,int weight){
 std::string numberText=std::to_string(number);
        int leadingZeros=weight-numberText.length();
       return  numberText=std::string(leadingZeros,'0')+numberText;
}


int main(){
    Color grey = {0, 0, 0, 255};
    Color yellow = {243, 216, 63, 255};
    int offset = 50;
    int windowWidth = 750;
    int windowHeigth = 700;

    InitWindow(windowWidth + offset, windowHeigth + 2 * offset, "EARTH INVADERS");  

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);  
    Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");    

    SetTargetFPS(60);
    Game game;
 

    while(WindowShouldClose() == false){

        game.HandleInput();
        game.Update();

        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);
        if(game.run){
            DrawTextEx(font, "Kill TheM", {570, 740}, 34, 2, yellow);
        } else {
            DrawTextEx(font, "PRESS ENTER", {50, 740}, 34, 2, yellow);
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);
        }
    
        float x = 50.0;
        for(int i = 0; i < game.lives; i ++) {
            DrawTextureV(spaceshipImage, {x, 745}, WHITE);  
            x += 50;
        }
        DrawTextEx(font,"SCORE",{50,15},34,2,yellow);
        std::string scoreText=FormatWithLeadingZeros(game.score,5);
        DrawTextEx(font,scoreText.c_str(),{50,40},34,2,yellow);
       
        game.Draw();
 
        EndDrawing();


    }
    CloseWindow();


}
