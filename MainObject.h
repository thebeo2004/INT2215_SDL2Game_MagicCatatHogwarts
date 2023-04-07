#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"

int NUM_FRAME_CHARACTER[] = {6, 6, 11, 6, 5, 8, 8, 4, 16, 18};

class MainObject : public BaseObject
{
    private:
        //position of frame
        int x_pos_, y_pos_;

        SDL_Rect frame_clip_[20];

        //Thự tứ của từng frame trong từng trạng thái.
        int frame;

        int status_;

        int life_point;

        bool is_free;

        bool is_dead, is_scared;

        enum Animation
        {
            RUNNING, SCARED, WAITING,
            DRAWING, HEART, LIGHTNING, SUNKEN,
            HURT, DIE, VICTORY,
        };

        //serve to unleash the ultimate skill
        //lightning_time: Expecto Petronum
        //sunken_time: Wingdadium Leviosa
        int lightning_time, sunken_time;
        bool is_lightning, is_sunken;

    public:
        MainObject();
        ~ MainObject();
        void render();
        void HandelInputAction(SDL_Event events);
        void set_clips();
        int getPosX();
        int getPosY();
        void hurt();
        //Calculate Real Position of Entity
        Entity getReal_Position();
        
        bool check_lightning();
        bool check_sunken();
};