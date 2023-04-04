#pragma once
#include "Skill.h"

Skill::Skill()
{
    frame = 0;
    set_clips();
    is_attack = false;
}

Skill::~Skill()
{
    free();
}

void Skill::set_clips()
{
    for(int i = 0; i <= 2; i++)
    {
        frame_clip_[i].x = i*FRAME_LIGHTNING_WIDTH;
        frame_clip_[i].y = 0;
        frame_clip_[i].w = FRAME_LIGHTNING_WIDTH;
        frame_clip_[i].h = FRAME_LIGHTNING_HEIGHT;
    }
}

void Skill::render(int x, int y)
{
    if (is_attack && frame < 3)
    {
        BaseObject::loadFromFile("skill/lightning_attack.png");
        SDL_Rect renderquad = {x - 10, 0, FRAME_LIGHTNING_WIDTH/2, y + 10};
        SDL_RenderCopy(gRenderer, mTexture, &frame_clip_[frame], &renderquad);
        frame++;
    }
    else
    {
        is_attack = false;
        frame = 0;
    }
}

void Skill::Attack()
{
    is_attack = true;
}

