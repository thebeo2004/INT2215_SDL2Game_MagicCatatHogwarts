#pragma once

#include "Tittle.h"

Tittle::Tittle()
{
    step = 0;

    status_ = -1;

    x = -LENGTH_TITTLE;

    y = 75;

    time = 0;
}

Tittle::~Tittle()
{
    free();
}

void Tittle::expecto()
{
    status_ = EXPECTO_PATRONUM;

    step = LENGTH_TITTLE / NUM_FRAME_TITTLE[status_];

    loadFromFile("tittle/Expecto Patronum Tittle.png");

    x = -LENGTH_TITTLE;
}

void Tittle::wingardium()
{
    status_ = WINGARDIUM_LEVIOSA;

    step = LENGTH_TITTLE / NUM_FRAME_TITTLE[status_];

    loadFromFile("tittle/Wingardium Leviosa Tittle.png");

    x = -LENGTH_TITTLE;
}

void Tittle::stupefy()
{
    status_ = STUPEFY;

    step = LENGTH_TITTLE / NUM_FRAME_TITTLE[status_];

    loadFromFile("tittle/Stupefy Tittle.png");

    x = -LENGTH_TITTLE;
}

void Tittle::transfer()
{
    status_ = -1;
}

void Tittle::render()
{
    if (status_ >= 0)
    {
        if (x < 0)
        {
            SDL_Rect renderquad = {x, y, mWidth, mHeight + 3};

            SDL_RenderCopy(gRenderer, mTexture, NULL, &renderquad);

            x = min(0, x + step);

            time = SDL_GetTicks();
        }
        else
        {
            if (SDL_GetTicks() - time <= 1000)
            { 
                SDL_Rect renderquad = {x, y, mWidth, mHeight + 3};

                SDL_RenderCopy(gRenderer, mTexture, NULL, &renderquad);
            }
            else
                status_ = -1;
        }
    }
}