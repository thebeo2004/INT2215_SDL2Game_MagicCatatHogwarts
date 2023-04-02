#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"
#include "LoadFont.h"
#include "LoadFont.cpp"

int NUM_FRAME_THREAT[] = {1, 1, 7, 7, 3, 3, 8};

class ThreatsObject: public BaseObject
{
    private:
        int x_pos_, y_pos_;

        int max_x, max_y;

        int x_val_, y_val_;

        SDL_Rect frame_clip_[10];

        int frame;
        //check if threat is die, normal, waiting????
        int status_;

        int life_point;
        //avoid holding mouse buttion constantly
        bool is_free;

        bool is_right, is_top;

        enum Animation
        {
            NORMAL_RIGHT, NORMAL_LEFT,
            ATTACK_RIGHT, ATTACK_LEFT,
            HURT_RIGHT, HURT_LEFT,
            DIE,
        };

        Font gText;

    public:
        ThreatsObject();
        ~ThreatsObject();

        void render();

        void HandleInputAction(SDL_Event events);

        void set_clips();
        //Check that mouse is in frame of threat
        bool isInside(int x, int y);
        //return position X of threat
        int getPosX();
        //return position Y of threat
        int getPosY();
        //set value of step
        void setVal();

        void setPos(int PosX, int PosY);

        void Update_Pos();

        void attack();
        //Calculate real position of Entity
        Entity getReal_Position();

        bool is_dead;
};
