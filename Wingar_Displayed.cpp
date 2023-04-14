#pragma once

#include "Wingar_Displayed.h"

Wingar::Wingar()
{
    is_loaded = false;
}

Wingar::~Wingar()
{
    free();
}

void Wingar::set_clip()
{
    for(int i = 0; i < 9; i++)
    {
        frame_clip[i].x = i*31;
        frame_clip[i].y = 0;
        frame_clip[i].w = 31;
        frame_clip[i].h = 50;
    }
}

void Wingar::render()
{
    if (!is_loaded)
        loadFromFile("character/wingar_displayed.png"),
        is_loaded = true;

    SDL_Rect renderquad = {SCREEN_WIDTH/2 + 120, 0, 31, 50};

    SDL_RenderCopy(gRenderer, mTexture, &frame_clip[frame_], &renderquad);

    frame_ = (frame_ + 1) % 9;
}