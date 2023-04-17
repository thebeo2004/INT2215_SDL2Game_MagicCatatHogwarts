#pragma once

#include "Menu.h"

Menu::Menu()
{
    is_playing = false;

    is_updateSmoke = false;

    is_intro1 = true;

    intro = NULL;
}

Menu::~Menu()
{
    free();
    smoke_left.free();
    smoke_right.free();

    Mix_FreeChunk(intro);
    intro = NULL;

    Mix_FreeChunk(move_mouseEffect);
    move_mouseEffect = NULL;
}

bool Menu::playing()
{
    intro = Mix_LoadWAV("sound/intro.ogg");
    move_mouseEffect = Mix_LoadWAV("sound/menu_music.ogg");

    return is_playing;
}

void Menu::render()
{
    if (!is_updateSmoke)
        smoke_left.Update_LeftRight(true),
        smoke_right.Update_LeftRight(false),
        is_updateSmoke = true;

    if (is_intro1)
        loadFromFile("menu/intro1.png");
    else
        loadFromFile("menu/intro2.png");

    SDL_Rect renderquad = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderquad);

    smoke_left.render();

    smoke_right.render();
}

void Menu::HandleInputAction(SDL_Event e)
{
    if ((e.button.x > 0 && e.button.x < SCREEN_WIDTH) && 
        (e.button.y > 0 && e.button.y < SCREEN_HEIGHT))
    {
        if (is_intro1)
            Mix_PlayChannel(-1, move_mouseEffect, 0);

        is_intro1 = false;

        if (e.type == SDL_MOUSEBUTTONDOWN)
            is_playing = true,
            free(),
            smoke_left.free(),
            smoke_right.free(),
            Mix_FreeChunk(move_mouseEffect),
            Mix_PlayChannel(-1, intro, 0);
    }

    else is_intro1 = true;
}