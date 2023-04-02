#pragma once

#include "ThreatsObject.h"
#include <iostream>

ThreatsObject::ThreatsObject()
{
    frame = 0;
    
    life_point = 1 + rand() % 2;

    is_free = true;

    is_dead = false;

    max_x = 220 + rand() % 130;

    max_y = 100 + rand() % 130;
}

Entity ThreatsObject::getReal_Position()
{
    Entity ans(x_pos_ + 45, x_pos_ + FRAME_THREAT_WIDTH - 46,
                y_pos_ + 37, y_pos_ + FRAME_THREAT_HEIGHT - 38);

    return ans;
}

void ThreatsObject::setVal()
{
    x_val_ = 3 + SDL_GetTicks()/6000;

    y_val_ = 2 + SDL_GetTicks()/7000;
}

void ThreatsObject::setPos(int PosX, int PosY)
{
    x_pos_ = PosX;

    y_pos_ = PosY;

    setVal();

    Entity pos = getReal_Position();

    int midX = (pos.x_left + pos.x_right)/2;

    int midY = (pos.y_top + pos.y_down)/2;

    if (midX < SCREEN_WIDTH/2) is_right = false;
    else is_right = true;

    if (midY < SCREEN_HEIGHT/2) is_top = true;
    else is_top = false;

    if (is_right)
        status_ = NORMAL_RIGHT;
    else
        status_ = NORMAL_LEFT;

    gText.SetFont(gFont_threat);
}

ThreatsObject::~ThreatsObject() {BaseObject::free();}

void ThreatsObject::Update_Pos()
{
    if (is_right)
    {
        x_pos_ -= x_val_;
        x_pos_ = max(x_pos_, max_x);
    }
    else
    {
        x_pos_ += x_val_;
        x_pos_ = min(x_pos_, max_x);
    }

    if (is_top)
    {
        y_pos_ += y_val_;
        y_pos_ = min(y_pos_, max_y);
    }
    else
    {
        y_pos_ -= y_val_;
        y_pos_ = max(y_pos_, max_y);
    }
}

int ThreatsObject::getPosX() {return x_pos_;}

int ThreatsObject::getPosY() {return y_pos_;}

void ThreatsObject::attack()
{
    if (is_right)
    {
        status_ = ATTACK_RIGHT;
        x_pos_ += 50;
    }
    else
    {
        status_ = ATTACK_LEFT;
        x_pos_ -= 50;
    }

    if (is_top) y_pos_ -= 30;
    else y_pos_ += 30;

    frame = 0;
}

void ThreatsObject::set_clips()
{
    if (mWidth > 0 && mHeight > 0)
    {
        for(int i = 0; i < 10; i++)
        {
            frame_clip_[i].x = i*FRAME_THREAT_WIDTH;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = FRAME_CHARACTER_WIDTH;
            frame_clip_[i].h = FRAME_CHARACTER_HEIGHT;
        }
    }
}

bool ThreatsObject::isInside(int x, int y)
{
    Entity pos = ThreatsObject::getReal_Position();
    if (x >= pos.x_left && x <= pos.x_right
        && y >= pos.y_top && y <= pos.y_down) return true;

    return false;
}

void ThreatsObject::render()
{
    if (status_ == DIE)
    {
        if (frame < NUM_FRAME_THREAT[DIE])
            BaseObject::loadFromFile("threats/die.png");
        else
        {
            if (!is_dead)
            {
                is_dead = true;
                BaseObject::free();
                gText.free();
                x_pos_ = 0;
                y_pos_ = 0;
            }
            else return;
        }
    }
    else
    {
        if (is_right)
        {
            if (status_ == ATTACK_RIGHT && frame < NUM_FRAME_THREAT[status_])
                BaseObject::loadFromFile("threats/attack_right.png");

            else if (status_ == HURT_RIGHT && frame < NUM_FRAME_THREAT[status_])
                BaseObject::loadFromFile("threats/hurt_right.png");

            else
            {
                BaseObject::loadFromFile("threats/normal_right.png");

                frame = 0;

                status_ = NORMAL_RIGHT;

                Update_Pos();
            }
        }
        else
        {
            if (status_ == ATTACK_LEFT  && frame < NUM_FRAME_THREAT[status_])
                BaseObject::loadFromFile("threats/attack_left.png");

            else if (status_ == HURT_LEFT && frame < NUM_FRAME_THREAT[status_])
                BaseObject::loadFromFile("threats/hurt_left.png");

            else
            {
                BaseObject::loadFromFile("threats/normal_left.png");

                frame = 0;

                status_ = NORMAL_LEFT;

                Update_Pos();
            }
        }
    }

    SDL_Rect renderquad = {x_pos_, y_pos_, FRAME_THREAT_WIDTH, FRAME_THREAT_HEIGHT};

    SDL_RenderCopy(gRenderer, mTexture, &frame_clip_[frame], &renderquad);

    frame++;

    string txt;
    txt += char(life_point + 48);
    gText.loadFromRenderedText(txt, {44, 39, 37});
    gText.render(x_pos_ + 66, y_pos_ + 10);
}

void ThreatsObject::HandleInputAction(SDL_Event events)
{
    if (status_ == DIE) return;

    if (events.type == SDL_MOUSEBUTTONDOWN)
    {
        if (is_free)
        {
            is_free = false;

            if (isInside(events.button.x, events.button.y))
            {
                life_point -= 1;

                if (life_point <= 0) status_ = DIE;

                else
                {
                    if (is_right)
                        status_ = HURT_RIGHT;
                    else
                        status_ = HURT_LEFT;
                }

                frame = 0;
            }

        }
    }
    else if (events.type == SDL_MOUSEBUTTONUP)
    {
        is_free = true;
    }
}

