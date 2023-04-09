#pragma once

#include "BaseObject.h"
#include "CommonFunc.h"

int NUM_FRAME_TITTLE[] = {25, 18, 5};

const int LENGTH_TITTLE = 313;

class Tittle : public BaseObject
{
    public:
        Tittle();
        ~Tittle();

        void render();

        void expecto();
        void wingardium();
        void stupefy();

        enum ultimate_skill
        {
            EXPECTO_PATRONUM, WINGARDIUM_LEVIOSA, 
            STUPEFY,
        };

        void transfer();

    private:

        int x, y;

        int step;

        int status_;

        int time;
};