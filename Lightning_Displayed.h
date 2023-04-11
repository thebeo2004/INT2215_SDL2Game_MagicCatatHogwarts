#pragma once

#include "BaseObject.h"
#include "CommonFunc.h"
#include "LoadFont.h"
#include "LoadFont.cpp"

class Lightning : public BaseObject
{
    public:
        Lightning();
        ~Lightning();

        void render(int num);

        void set_clip();

        SDL_Rect frame_clip[6];

        Font gText;

        void SetFont();
        void loadFont(int num);

    private:
        bool is_loaded;

        int frame_;
};
