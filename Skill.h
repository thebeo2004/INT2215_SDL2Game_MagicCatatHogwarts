#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"

const int FRAME_LIGHTNING_WIDTH = 300;
const int FRAME_LIGHTNING_HEIGHT = 682;

class Skill : public BaseObject
{
    private:
        int frame;
        SDL_Rect frame_clip_[3];
        bool is_attack;
    public:
        Skill();
        ~Skill();
        void set_clips();
        void render(int x, int y);
        void Attack();

};