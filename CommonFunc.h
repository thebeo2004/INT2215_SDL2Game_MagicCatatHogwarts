#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <bits/stdc++.h>

using namespace std;

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 480;

const int FRAME_CHARACTER_WIDTH = 190;
const int FRAME_CHARACTER_HEIGHT = 170;

const int FRAME_THREAT_WIDTH = 150;
const int FRAME_THREAT_HEIGHT = 150;

const int FRAME_PER_SECOND = 20;

//calculate real position of object in frame
struct Entity
{
    int x_left;
    int x_right;
    int y_top;
    int y_down;

    Entity(int _left, int _right, int _top, int _down)
    {
        x_left = _left;
        x_right = _right;
        y_top = _top;
        y_down = _down;
    }
};

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;

bool isCollision(Entity a, Entity b)
{

    int x_left = max(a.x_left, b.x_left);
    int x_right = min(a.x_right, b.x_right);

    int y_top = max(a.y_top, b.y_top);
    int y_down = min(a.y_down, b.y_down);

    if (x_left >= x_right)
        return false;

    if (y_down <= y_top)
        return false;

    return true;

}

#define MP make_pair

vector<pair<int, int>> RANDOM_POSITION = {{-119, 164}, {-117, 240}, {-105, 118}, {-122, 31}, {-134, 4}, {-115, -81}, {-27, -94}, {76, -90}, {153, -90}, {240, -86}, {33, 457}, {140, 464}, {240, 457}, {381, 459}, {460, 430}, {559, 416}, {639, 408}, {659, 315}, {646, 276},  {646, 200}, {640, 95}, {637, 44}, {649, -16}, {630, -84}, {571, -84}, {505, -75}, {444, -82}, {383, -69}};


