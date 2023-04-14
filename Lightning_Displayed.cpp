#pragma once

#include "Lightning_Displayed.h"

Lightning::Lightning()
{
    is_loaded = false;

    frame_ = 0;
}

Lightning::~Lightning()
{
    free();
}

void Lightning::set_clip()
{
    for(int i = 0; i < 6; i++)
    {
        frame_clip[i].x = 20*i;
        frame_clip[i].y = 0;
        frame_clip[i].w = 20;
        frame_clip[i].h = 50;
    }
}

void Lightning::SetFont()
{
    gText.SetFont(gFont_22);
}

void Lightning::loadFont(int num)
{
    if (num < 0) return;

    string txt = "x ";
    txt += char(num + 48);
    gText.loadFromRenderedText(txt, {168, 193, 208});
    
    // cerr << gText.getWidth() << " " << gText.getHeight() << "\n";
    gText.render(SCREEN_WIDTH/2 + 30, 12);
}

void Lightning::render(int num)
{
    if (!is_loaded)
        loadFromFile("character/lightning_displayed.png"),
        is_loaded = true;
    // if (num > 0)

    SDL_Rect renderquad = {SCREEN_WIDTH/2, -5, 20, 50};
        
    SDL_RenderCopy(gRenderer, mTexture, &frame_clip[frame_], &renderquad);

    frame_ = (frame_ + 1) % 6;


    loadFont(num);
}