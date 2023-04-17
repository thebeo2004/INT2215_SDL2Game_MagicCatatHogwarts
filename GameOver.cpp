#pragma once

#include "GameOver.h"

Over::Over() {};

Over::~Over()
{
    free();

    score_displaying.free();
}

void Over::SetFont()
{
    score_displaying.SetFont(gFont_38);
    result_displaying.SetFont(gFont_40);
}

string Over::convert(int a)
{
    string ans;

    if (a == 0) ans = "0";

    while(a > 0)
        ans = char(a%10 + 48) + ans,
        a/= 10;

    return ans;
}

void Over::victory(int score)
{
    is_victory = true;

    result_displaying.loadFromRenderedText("High Score", {246, 246, 246});

    score_displaying.loadFromRenderedText(convert(score), {246, 246, 246});
}

void Over::lose()
{
    is_victory = false;

    result_displaying.loadFromRenderedText("You lost", {246, 246, 246});
}

void Over::render()
{
    if (is_victory)
    {
        loadFromFile("menu/victory.png");

        SDL_Rect renderquad = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

        SDL_RenderCopy(gRenderer, mTexture, NULL, &renderquad);

        result_displaying.render(SCREEN_WIDTH - 295, 150);
        
        score_displaying.render(SCREEN_WIDTH - 150 - score_displaying.getWidth(), 200);
    }
    else
    {
        loadFromFile("menu/failure.png");

        SDL_Rect renderquad = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

        SDL_RenderCopy(gRenderer, mTexture, NULL, &renderquad);

        result_displaying.render(SCREEN_WIDTH - 300, 150);
    }
}