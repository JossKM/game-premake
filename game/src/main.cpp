/*
READ DOCUMENTATION AND SEE EXAMPLE CODE HERE! https://www.raylib.com/index.html
*/

/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event 
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial 
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you 
--  wrote the original software. If you use this software in a product, an acknowledgment 
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include "raylib.h"
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "game.h"   // an external header in this project
#include "lib.h"	// an external header in the static lib project
#include <string>

#define FPS 60
float time = 0;
float dt = 1.0f / FPS;

Vector2 position;
Vector2 velocity;

float a = 5;
float b = 100;

void GameInit()
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(InitialWidth, InitialHeight, "Game Physics - Joss Moo-Young - 123456789");
    SetTargetFPS(FPS);

    position = Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
}

void GameCleanup()
{
    CloseWindow();
}

bool GameUpdate()
{
    //Respond to Input
    if (IsKeyDown(KEY_RIGHT)) velocity.x += 8.0f;
    if (IsKeyDown(KEY_LEFT)) velocity.x -= 8.0f;
    if (IsKeyDown(KEY_UP)) velocity.y -= 8.0f;
    if (IsKeyDown(KEY_DOWN)) velocity.y += 8.0f;

    
    //Update world
    position += velocity * dt;

    position.x += (-sin(time * a)) * a * b * dt;
    position.y += (cos(time * a)) * a * b * dt;


    //Update time
    time += dt;
    return true;
}

void GameDraw()
{
    BeginDrawing();
    ClearBackground(DARKGRAY);
    
    //Draw Objects
    DrawCircle(position.x, position.y, 30, RED);
    DrawCircle(500 + cos(time * a) * b, 500 + sin(time * a) * b, 30, GREEN);

    // Draw GUI controls
          //------------------------------------------------------------------------------
    GuiSliderBar(Rectangle { 900, 40,  120, 20 }, "A", TextFormat("%.2f", a), & a, -10, 10);
    GuiSliderBar(Rectangle { 900, 70,  120, 20 }, "B", TextFormat("%.2f", b), & b, -500, 500);
    //------------------------------------------------------------------------------

    DrawText("Joss Moo-Young", 10, GetScreenHeight() - 20, 20, GetTextColor());

    EndDrawing();
}

int main()
{
    GameInit();

    while (!WindowShouldClose())
    {
        if (!GameUpdate())
            break;

        GameDraw();
    }
    GameCleanup();

    return 0;
}