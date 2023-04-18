#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"

class Support : public BaseObject
{
    private:
        int x_pos, y_pos;

        int frame;

        //Cài đặt số lần còn lượng target mạng đều tiên của main -> Hiển thị để hồi mạng
        int target;

        bool is_displayed;

        bool is_dead;

        bool is_loaded;

        SDL_Rect frame_clip_[5];

    public:

        Support(int x, int y, int num);

        ~Support();

        void set_clips();

        bool HandleInputAction(SDL_Event events);

        void check_Displaying(int num);

        bool isInside(int x, int y);

        void render();
};