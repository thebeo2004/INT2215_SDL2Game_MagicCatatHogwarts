#pragma once

#include "CommonFunc.h"

class ImpTimer
{
    public:
        ImpTimer();
        ~ImpTimer();

        void start();
        void stop();
        void pause();
        void unpause();

        int get_ticks();

        bool isStarted();
        bool isPaused();
    
    private:
        int start_tick_;
        int paused_tick_;

        bool mPaused;
        bool mStarted;
};