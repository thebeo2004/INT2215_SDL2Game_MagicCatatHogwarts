#pragma once

#include "Support.h"

Support::Support(int x, int y, int num)
{
    x_pos = x;

    y_pos = y;

    target = num;

    is_displayed = false;

    is_dead = false;

    is_loaded = false;

    frame = 0;
}

Support::~Support()
{
    free();
}

void Support::set_clips()
{

    for(int i = 0; i < 5; i++)
    {
        frame_clip_[i].x = i * 50;
        frame_clip_[i].y = 0;
        frame_clip_[i].w = 50;
        frame_clip_[i].h = 50;
    }
}

bool Support::isInside(int x, int y)
{
    if ((x >= x_pos && x <= x_pos + 80) && (y >= y_pos && y <= y_pos + 80))
        return true;

    return false;
}

void Support::check_Displaying(int num)
{
    if (num <= target && !is_loaded)
    {
        is_loaded = true;

        is_displayed = true;
    }
}

void Support::render()
{
    if (is_dead || frame > 80)
    {
        free();

        x_pos = 0;

        y_pos = 0;

        is_displayed = false;
    }
    else if (is_displayed)
    {
        loadFromFile("character/support.png");

        SDL_Rect renderquad = {x_pos, y_pos, 80, 80};

        SDL_RenderCopy(gRenderer, mTexture, &frame_clip_[frame % 5], &renderquad);

        frame++;
    }
}

bool Support::HandleInputAction(SDL_Event e)
{
    if (is_displayed)
    {
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (isInside(e.button.x, e.button.y))
            {
                is_dead = true;

                return true;
            }
        }
    }

    return false;
}

