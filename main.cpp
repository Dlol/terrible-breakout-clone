#include <cstdlib>
#include <raylib.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
// global variables
int screenWidth = 800;
int screenHeight = 800;
bool blocks[8*4];

// helper functions
void centerRect(int x, int y, int width, int height, Color color) {
	DrawRectangle((x - (width / 2)), (y - (height / 2)), width, height, color);
}

void centerRectLines(int x, int y, int width, int height, Color color) {
	DrawRectangleLines((x - (width / 2)), (y - (height / 2)), width, height, color);
}

void ballBounce(Vector2 &direction){
    direction.y = direction.y * -1;
}

// paddle
void paddle(int &paddlex, int &paddley) {
    int direction = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);
    int speed = 8;
    paddlex += direction * speed;
    if(paddlex - 100 < 0 || paddlex + 100 > screenWidth){
        paddlex -= direction * speed;
    }
    centerRect(paddlex, paddley, 200, 24, BLACK);
}

// ball
void ball(int &ballx, int &bally, int paddley, int paddlex, Vector2 &direction){
    int ballspeed = 4;
    // check y collision
    if(bally - 10 < 0 /*|| bally + 10 > screenHeight*/){
        direction.y = direction.y * -1;
        // std::cout << "y: " << direction.y << std::endl;
    }
    // check x collision
    if(ballx - 10 < 0 || ballx + 10 > screenHeight){
        direction.x = direction.x * -1;
        // std::cout << "x: " << direction.x << std::endl;
    }
    // paddle collision
    if(bally - 10 > paddley - 30 && bally + 10 < paddley + 30){
        if(ballx - 10 > paddlex - 100 && ballx + 10 < paddlex + 100){
            direction.y = direction.y * -1;
        }
    }
    // ball movey movey
    ballx += direction.x * ballspeed;
    bally += direction.y * ballspeed;
    DrawCircle(ballx, bally, 10, RED);
}

// generate the blocks
void genBlocks(int ballx, int bally, Vector2 &direction){
    for (int index = 0; index < sizeof(blocks)/sizeof(blocks[0]); index += 1) {
        int x = index % 8 * 100 + 4;
        int y = std::floor(index / 8) * 40 + 4;
        int width = 100 - 8;
        int height = 40 - 8;
        if (bally - 10 > y - 4 && bally + 10 < y + height + 4) {
            if (ballx - 10 > x - 4 && ballx + 10 < x + width + 4 && blocks[index]) {
                blocks[index] = false;
                ballBounce(direction);
            }
        }
        if (blocks[index]) {
            // std::cout << "y: " << ind << std::endl;
            DrawRectangle(x, y, width, height, SKYBLUE);
        }
    }
}

// main
int main() {
	InitWindow(screenWidth, screenHeight + 30, "raylib example");
	SetTargetFPS(60);
    int paddlex, paddley, ballx, bally;
    paddlex = screenWidth / 2;
    paddley = 780;
    srand(time(NULL));
    ballx = rand() % 880 + 10;
    bally = 400;
    Vector2 direction = {
        0.9,
        1
    };
    bool playing = true;
    for (int index = 0; index < sizeof(blocks)/sizeof(blocks[0]); index += 1) {
        blocks[index] = true;
    }
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        if (playing){
            paddle(paddlex, paddley);
            genBlocks(ballx, bally, direction);
            ball(ballx, bally, paddley, paddlex, direction);
            if (bally + 10 > screenHeight){
                playing = false;
            }
        }
        else {
            DrawText("DEAD", 16, 16, 30, RED);
            DrawText("no restarting", 16, 46, 30, RED);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
