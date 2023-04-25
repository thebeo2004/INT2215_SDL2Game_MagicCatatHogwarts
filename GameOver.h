#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"
#include "LoadFont.h"
#include "LoadFont.cpp"

class Replay : public BaseObject
{
    public:
        Replay()
        {
            frame = 0;
            
            for(int i = 0; i < 2; i++)
            {
                frame_clip[i].x = 75*i;
                frame_clip[i].y = 0;
                frame_clip[i].w = 75;
                frame_clip[i].h = 73;
            }

            is_light = false;

            is_loadSound_effect = false;
        }

        ~Replay()
        {
            BaseObject::free();

            Mix_FreeChunk(sound_effect);

            sound_effect = NULL;
        }

        void render()
        {
            if (!is_loadSound_effect)
                sound_effect = Mix_LoadWAV("sound/mouse1.ogg"),
                is_loadSound_effect = true;

            loadFromFile("menu/return.png");

            SDL_Rect renderquad = {SCREEN_WIDTH - 230, 325, 75, 73};

            if (!is_light) 
                SDL_RenderCopy(gRenderer, mTexture, &frame_clip[0], &renderquad);
            else
                SDL_RenderCopy(gRenderer, mTexture, &frame_clip[1], &renderquad);
        }

        void Light()
        {
            if (!is_light)
                Mix_PlayChannel(-1, sound_effect, 0);

            is_light = true;
        }

        void Dark() {is_light = false;}

    private:

        int frame;

        bool is_light;

        SDL_Rect frame_clip[3];

        Mix_Chunk* sound_effect;

        bool is_loadSound_effect;
};

class Over : public BaseObject
{
    public:

        Over();
        ~Over();

        void render();

        void SetFont();

        void victory(int score);

        void lose();

        string convert(int num);

        void HandelInputAction(SDL_Event e);

        bool Replay_Game();

        void initialize();
    private:

        //txt: "High Score", highscore_displaying: High Score
        Font txt, highscore_displaying;
        //score_displaying: your score, result_displaying: "You lost"/"Your score"
        Font result_displaying, score_displaying;

        Replay replay;

        bool is_victory;

        bool is_replay;

        //Điểm hiện tại có phải là highscore
        bool is_highscore;
};