#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Tittle.h"
#include "Tittle.cpp"
#include "Heart_Displayed.h"
#include "Heart_Displayed.cpp"
#include "Lightning_Displayed.h"
#include "Lightning_Displayed.cpp"
#include "Wingar_Displayed.h"
#include "Wingar_Displayed.cpp"

int NUM_FRAME_CHARACTER[] = {6, 6, 11, 6, 8, 8, 8, 4, 16, 36};

class MainObject : public BaseObject
{
    private:
        //position of frame
        int x_pos_, y_pos_;

        SDL_Rect frame_clip_[36];

        //Thự tứ của từng frame trong từng trạng thái.
        int frame;

        int status_;

        int life_point;

        bool is_free;

        //is_dead: Để giữ cho trạng thái va chạm
        bool is_dead, is_scared;

        //Xác định trạng thái game, sau khi đã load hết frame die/victory
        bool game_over;

        //Số lần sử dụng skill expecto
        //threats_die -> Xác định số lượng threats die -> Cứ 10 threats die -> num++
        int num, threats_die;

        bool set_font;

        enum Animation
        {
            RUNNING, SCARED, WAITING,
            DRAWING, HEART, LIGHTNING, SUNKEN,
            HURT, DIE, VICTORY,
        };

        //chỉ là biến tạm thời -> Xác định khoảng thời gian nhấn phím để tung ra skill
        //lightning_time: Expecto Petronum
        //sunken_time: Wingdadium Leviosa
        int lightning_time, sunken_time;

        //Phục vụ việc xem đã đủ 5s chưa kể từ lần sử dụng Wingar gần nhất.
        int wingar_time;
        bool is_wingartime;

        bool is_lightning, is_sunken;

        Tittle ultimate_skill;

        Heart heart_displayed;
        Lightning lightning_displayed;
        Wingar wingar_displayed;

        Mix_Chunk* mouse_effect;
        Mix_Chunk* victory_effect;
        Mix_Chunk* lose_effect;
        Mix_Chunk* expectopetronum_effect;
        Mix_Chunk* wingdardiumleviosa_effect;
        Mix_Chunk* stupefy_effect;
        Mix_Chunk* thunder_effect;
        Mix_Chunk* wind_effect;
    
    public:
        MainObject();
        ~ MainObject();

        void render();

        void HandelInputAction(SDL_Event events);

        void set_clips();

        void free();

        int getPosX();
        int getPosY();

        void hurt();

        //Calculate Real Position of Entity
        Entity getReal_Position();
        
        bool check_lightning();

        bool check_sunken();

        //Update thời gian và check xem đã đủ 5s kể từ lần cuối dùng Wingar hay chưa?
        void Update_WingarTime();

        void Count_ThreatsDie(int num_die);

        int get_LifePoint();

        void Heal();

        bool is_gameover();

        void victory();
};