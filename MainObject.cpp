#pragma once

#include "MainObject.h"

MainObject::MainObject()
{
    x_pos_ = -75;
    y_pos_ = 130;
    frame = 0;
    status_ = WAITING;
    is_free = true;
    is_dead = false;
    life_point = 5;

    is_scared = true;
}

MainObject::~MainObject()
{
    BaseObject::free();
}

int MainObject::getPosX()
{
    return x_pos_;
}

int MainObject::getPosY()
{
    return y_pos_;
}

void MainObject::hurt()
{
    life_point -= 1;

    if (life_point <= 0)
    {
        status_ = DIE;
        if (!is_dead) frame = 0, is_dead = true;
    }
    else status_ = HURT, frame = 0;
}

void MainObject::set_clips()
{
    if (mWidth > 0 && mHeight > 0)
    {
        for(int i = 0; i < 20; i++)
        {
            frame_clip_[i].x = i*FRAME_CHARACTER_WIDTH;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = FRAME_CHARACTER_WIDTH;
            frame_clip_[i].h = FRAME_CHARACTER_HEIGHT;
        }
    }
}


void MainObject::render()
{

    if (x_pos_ < 270)
    {
        loadFromFile("character/running.png");

        x_pos_ += 15;

        status_ = RUNNING;

        frame = (frame % NUM_FRAME_CHARACTER[status_]);
    }
    else
    {
        if (SDL_GetTicks() >= 2900 && is_scared)
        {
            frame = 0;
            status_ = SCARED;
            is_scared = false;
        }

        if (status_ == DIE)
        {
            if (frame < NUM_FRAME_CHARACTER[status_])
                loadFromFile("character/die.png");
            else BaseObject::free();
        }
        else if (status_ == SCARED && frame < NUM_FRAME_CHARACTER[status_])
            loadFromFile("character/scared.png");
        else if (status_ == HURT && frame < NUM_FRAME_CHARACTER[status_])
            loadFromFile("character/hurt.png");
        else if (status_ == DRAWING && frame < NUM_FRAME_CHARACTER[status_]) 
            loadFromFile("character/drawing.png");
        else
        {
            status_ = WAITING;

            frame = (frame % NUM_FRAME_CHARACTER[status_]);

            loadFromFile("character/waiting.png");
        }
    }

    SDL_Rect renderquad = {x_pos_, y_pos_, FRAME_CHARACTER_WIDTH, FRAME_CHARACTER_HEIGHT};
    
    SDL_RenderCopy(gRenderer, mTexture, &frame_clip_[frame], &renderquad);

    frame += 1;
}

void MainObject::HandelInputAction(SDL_Event e)
{
    if (status_ == DIE) return;

    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (is_free)
        {
            is_free = false;

            if (!is_scared) status_ = DRAWING;

            frame = 0;
        }
    }
    else if (e.type == SDL_MOUSEBUTTONUP)
    {
        is_free = true;
    }
}

Entity MainObject::getReal_Position()
{
    Entity ans(x_pos_ + 44, x_pos_ + FRAME_CHARACTER_WIDTH - 59,
                y_pos_ + 76, y_pos_ + FRAME_CHARACTER_HEIGHT - 20);

    return ans;
}