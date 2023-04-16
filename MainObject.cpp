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

    threats_die = 0;
    num = 1;

    is_scared = true;

    lightning_time = 0;
    sunken_time = 0;

    is_lightning = false;
    is_sunken = false;

    heart_displayed.set_clip();
    lightning_displayed.set_clip();
    wingar_displayed.set_clip();

    set_font = false;

    wingar_time = 0;
    is_wingartime = true;
}

MainObject::~MainObject()
{
    BaseObject::free();

    Mix_FreeChunk(mouse_effect);
    mouse_effect = NULL;

    Mix_FreeChunk(expectopetronum_effect);
    expectopetronum_effect = NULL;

    Mix_FreeChunk(wingdardiumleviosa_effect);
    wingdardiumleviosa_effect = NULL;

    Mix_FreeChunk(thunder_effect);
    thunder_effect = NULL;

    Mix_FreeChunk(wind_effect);
    wind_effect = NULL;

    Mix_FreeChunk(stupefy_effect);
    stupefy_effect = NULL;

    wingar_displayed.free();
    heart_displayed.free();
    lightning_displayed.free();

    ultimate_skill.free();
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
    mouse_effect = Mix_LoadWAV("sound/mouse0.mp3");
    expectopetronum_effect = Mix_LoadWAV("sound/expecto_patronum.mp3");
    wingdardiumleviosa_effect = Mix_LoadWAV("sound/wingdardium_leviosa.mp3");
    stupefy_effect = Mix_LoadWAV("sound/stupefy.mp3");
    thunder_effect = Mix_LoadWAV("sound/thunder.ogg");
    wind_effect = Mix_LoadWAV("sound/wind.ogg");

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
    is_lightning = false;
    is_sunken = false;

    ultimate_skill.render();

    heart_displayed.render(life_point);

    if (!set_font)
        lightning_displayed.SetFont(),
        set_font = true;

    lightning_displayed.render(num);

    if (is_wingartime) wingar_displayed.render();

    if (x_pos_ < 270)
    {
        loadFromFile("character/running.png");

        x_pos_ += 15;

        status_ = RUNNING;

        frame = (frame % NUM_FRAME_CHARACTER[status_]);
    }
    else
    {
        if (SDL_GetTicks() - time_start_playing >= 2900 && is_scared)
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
        else if (status_ == HEART && frame < NUM_FRAME_CHARACTER[status_])
            loadFromFile("character/heart.png");
        else if (status_ == DRAWING && frame < NUM_FRAME_CHARACTER[status_]) 
            loadFromFile("character/drawing.png");
        else if (status_ == LIGHTNING && frame < NUM_FRAME_CHARACTER[status_])
            loadFromFile("character/lightning.png");
        else if (status_ == SUNKEN && frame < NUM_FRAME_CHARACTER[status_])
            loadFromFile("character/sunken.png");
        else if (lightning_time > 0)
        {
            frame = frame % NUM_FRAME_CHARACTER[DRAWING];
            loadFromFile("character/drawing.png");
        }
        else if (sunken_time > 0)
        {
            frame = frame % NUM_FRAME_CHARACTER[DRAWING];
            loadFromFile("character/drawing.png");
        }
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

    if (e.type == SDL_KEYDOWN)
    {
        if ((e.key.keysym.sym == SDLK_RCTRL || e.key.keysym.sym == SDLK_LCTRL) && num > 0)
        {
            if (lightning_time == 0)
            {
                lightning_time = SDL_GetTicks();

                status_ = DRAWING;

                frame = 0;

                Mix_PlayChannel(3, expectopetronum_effect, 0);

                ultimate_skill.expecto();
            }
            else if (lightning_time > 0)
            {
                if (SDL_GetTicks() - lightning_time >= 2000)
                {
                    status_ = LIGHTNING;

                    frame = 0;

                    is_lightning = true;

                    lightning_time = -1;

                    Mix_PlayChannel(-1, thunder_effect, 0);
                }
                else
                {
                    status_ = DRAWING;
                    frame = 0;
                }
            }
        }
        else if ((e.key.keysym.sym == SDLK_RALT || e.key.keysym.sym == SDLK_LALT) && is_wingartime)
        {
            if (sunken_time == 0)
            {
                sunken_time = SDL_GetTicks();

                status_ = DRAWING;

                frame = 0;

                Mix_PlayChannel(3, wingdardiumleviosa_effect, 0);

                ultimate_skill.wingardium();
            }
            else if (sunken_time > 0)
            {
                if (SDL_GetTicks() - sunken_time >= 1300)
                {
                    status_ = SUNKEN;

                    frame = 0;

                    is_sunken = true;

                    sunken_time = -1;

                    Mix_PlayChannel(-1, wind_effect, 0);

                    // ultimate_skill.transfer();
                }
                else
                {
                    status_ = DRAWING;
                    frame = 0;
                }
            }
        }
    }
    else if (e.type == SDL_KEYUP)
    {
        if ((e.key.keysym.sym == SDLK_RCTRL || e.key.keysym.sym == SDLK_LCTRL) && num > 0)
        {  
            if (SDL_GetTicks() - lightning_time < 2000)
                ultimate_skill.transfer(),
                Mix_HaltChannel(3);

            lightning_time = 0;

            num--;
        }
        else if ((e.key.keysym.sym == SDLK_RALT || e.key.keysym.sym == SDLK_LALT) && is_wingartime)
        {
            if (SDL_GetTicks() - sunken_time < 2000)
                ultimate_skill.transfer(),
                Mix_HaltChannel(3);

            sunken_time = 0;
            wingar_time = SDL_GetTicks();
        }
    }

    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (is_free)
        {
            is_free = false;

            if (!is_scared) status_ = DRAWING;

            frame = 0;

            Mix_PlayChannel(-1, mouse_effect, 0);
        }
    }
    else if (e.type == SDL_MOUSEBUTTONUP)
    {
        is_free = true;
    }

    Update_WingarTime();
}

bool MainObject::check_lightning() {return is_lightning;}
bool MainObject::check_sunken() {return is_sunken;}

Entity MainObject::getReal_Position()
{
    Entity ans(x_pos_ + 44, x_pos_ + FRAME_CHARACTER_WIDTH - 59,
                y_pos_ + 76, y_pos_ + FRAME_CHARACTER_HEIGHT - 20);

    return ans;
}

void MainObject::Update_WingarTime()
{
    if (wingar_time == 0 || SDL_GetTicks() - wingar_time >= 3500)
        is_wingartime = true;
        
    else is_wingartime = false;
}

void MainObject::Count_ThreatsDie(int num_die)
{
    threats_die += num_die;

    num = min(5, num + threats_die/10);

    threats_die %= 10;
}

int MainObject::get_LifePoint()
{
    return life_point;
}

void MainObject::Heal()
{
    if (status_ == DIE) return;

    frame = 0;

    status_ = HEART;

    life_point++;

    Mix_PlayChannel(-1, stupefy_effect, 0);

    ultimate_skill.stupefy();
}