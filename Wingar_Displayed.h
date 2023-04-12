#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"

class Wingar : public BaseObject
{
    private:
        int frame_;

        SDL_Rect frame_clip[9];

        bool is_loaded;

    public:
        Wingar();
        ~Wingar();

        void set_clip();
        void render();

};