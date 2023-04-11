#pragma once

#include "BaseObject.h"
#include "CommonFunc.h"

class Heart : public BaseObject
{
    public:
        Heart();
        ~Heart();

        void render(int life_point);

        void set_clip();

    private:
        bool is_loaded;

        int frame_ = 0;

        SDL_Rect frame_clip[6];
};