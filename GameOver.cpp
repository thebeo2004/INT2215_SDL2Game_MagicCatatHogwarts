#pragma once

#include "GameOver.h"

Over::Over()
{
    initialize();
}

void Over::initialize()
{
    is_replay = false;
    is_highscore = false;
}

Over::~Over()
{
    free();

    score_displaying.free();

    result_displaying.free();

    highscore_displaying.free();

    txt.free();

    replay.free();
}

void Over::SetFont()
{
    score_displaying.SetFont(gFont_38);
    highscore_displaying.SetFont(gFont_38);

    result_displaying.SetFont(gFont_40);
    txt.SetFont(gFont_40);
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

    if (score >= high_score)
        high_score = score,
        is_highscore = true,
        txt.loadFromRenderedText("High Score", {246, 246, 246}),
        highscore_displaying.loadFromRenderedText(convert(score), {246, 246, 246});
    else
        txt.loadFromRenderedText("High Score", {246, 246, 246}),
        highscore_displaying.loadFromRenderedText(convert(high_score), {246, 246, 246}),
        result_displaying.loadFromRenderedText("Your Score", {246, 246, 246}),
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

        if (is_highscore)
            txt.render(SCREEN_WIDTH - 295, 150),
            highscore_displaying.render(SCREEN_WIDTH - 150 - highscore_displaying.getWidth(), 200);

        if (!is_highscore)
            txt.render(SCREEN_WIDTH - 295, 100),
            highscore_displaying.render(SCREEN_WIDTH - 150 - highscore_displaying.getWidth(), 150),
            result_displaying.render(SCREEN_WIDTH - 295, 200),
            score_displaying.render(SCREEN_WIDTH - 150 - score_displaying.getWidth(), 250);

    }
    else
    {
        loadFromFile("menu/failure.png");

        SDL_Rect renderquad = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

        SDL_RenderCopy(gRenderer, mTexture, NULL, &renderquad);

        result_displaying.render(SCREEN_WIDTH - 265, 150);
    }

    replay.render();
}

void Over::HandelInputAction(SDL_Event e)
{
    if ((e.button.x > SCREEN_WIDTH - 230 && e.button.x < SCREEN_WIDTH - 230 + 75) && 
        (e.button.y > 325 && e.button.y < 325 + 73))
            replay.Light();
    else replay.Dark();

    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if ((e.button.x > SCREEN_WIDTH - 230 && e.button.x < SCREEN_WIDTH - 230 + 75) && 
        (e.button.y > 325 && e.button.y < 325 + 73))
            is_replay = true;
    }
}

bool Over::Replay_Game()
{
    return is_replay;
}