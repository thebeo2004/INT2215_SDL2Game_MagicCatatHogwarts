#pragma once

#include "Heart_Displayed.h"

Heart::Heart() 
{
    is_loaded = false;
}

Heart::~Heart()
{
    free();
}

void Heart::set_clip()
{
    for(int i = 0; i < 6; i++)
    {
        frame_clip[i].x = i*50;
        frame_clip[i].y = 0;
        frame_clip[i].w = 50;
        frame_clip[i].h = 50;
    }
}

void Heart::render(int life_point)
{
    if (!is_loaded) 
        loadFromFile("character/heart_displayed.png"),
        is_loaded = true;

    frame_ = (frame_ + 1) % 6;

    for(int i = 1; i <= life_point; i++)
    {
        SDL_Rect renderquad = {(i - 1)*mWidth/6, 0, mWidth/6, mHeight};

        if (i == life_point)
            SDL_RenderCopy(gRenderer, mTexture, &frame_clip[frame_], &renderquad);
        else
            SDL_RenderCopy(gRenderer, mTexture, &frame_clip[0], &renderquad);
    }
}