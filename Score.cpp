#pragma once

#include "Score.h"

Score::Score()
{
    initialize();
}

void Score::initialize()
{
    score = 0;

    num_die = 0;

    score_loop = 0;
}

Score::~Score()
{
    score_displayed.free();
}

void Score::SetFont()
{
    score_displayed.SetFont(gFont_40);
    num_die_displayed.SetFont(gFont_38);
}

string Score::Convert(int a)
{
    string ans;

    if (a == 0) ans = "0";

    while(a > 0)
        ans = char(a%10 + 48) + ans,
        a/= 10;

    return ans;
}

void Score::Update_ScoreLoop(int a)
{
    if (a > 0)
        num_die++;

    score_loop += a;
}

void Score::Update_Score()
{
    score += score_loop * num_die;

    if (num_die != 0)
        num_die_displayed.loadFromRenderedText("x " + Convert(num_die), {255, 246, 3}),
        frame = 0;

    score_loop = 0;

    num_die = 0;
}

int Score::get_die()
{
    return num_die;
}

void Score::render()
{
    Update_Score();

    if (frame < 8)
        num_die_displayed.render(SCREEN_WIDTH/2 - 10, SCREEN_HEIGHT - 75);

    frame++;

    score_displayed.loadFromRenderedText(Convert(score), {216, 168, 30});

    score_displayed.render(SCREEN_WIDTH - 10 - score_displayed.getWidth(), 0);
}

int Score::get_score()
{
    return score;
}