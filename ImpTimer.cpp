#pragma once

#include "ImpTimer.h"

ImpTimer::ImpTimer()
{
    start_tick_ = 0;
    paused_tick_ = 0;

    mPaused = 0;
    mStarted = 0;
}

ImpTimer::~ImpTimer()
{

}

void ImpTimer::start()
{
    mStarted = true;
    mPaused = false;

    start_tick_ = SDL_GetTicks();
    paused_tick_ = 0;
}

void ImpTimer::stop()
{
    mStarted = false;
    mPaused = false;

    start_tick_ = 0;
    paused_tick_ = 0;
}

void ImpTimer::pause()
{
    if (mStarted && !mPaused)
    {
        mPaused = true;

        paused_tick_ = SDL_GetTicks() - start_tick_;
        start_tick_ = 0;
    }
}

void ImpTimer::unpause()
{
    if (mStarted && mPaused)
    {
        mPaused = false;

        start_tick_ = SDL_GetTicks() - paused_tick_;
        paused_tick_ = 0;
    }
}

int ImpTimer:: get_ticks()
{
    if (mStarted)
    {
        if (mPaused)
            return paused_tick_;
        else return SDL_GetTicks() - start_tick_;
    }

    return 0;
}

bool ImpTimer::isStarted()
{
    return mStarted;
}

bool ImpTimer::isPaused()
{
    return mPaused;
}