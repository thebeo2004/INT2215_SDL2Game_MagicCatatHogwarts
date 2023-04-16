#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"

const int FRAME_SMOKELEFT_WIDTH = 469;
const int FRAME_SMOKERIGHT_WIDTH = 663;

class Smoke: public BaseObject
{
    public:
        Smoke() {};

        ~Smoke()
        {
            free();
        }

        void Update_LeftRight(bool OwO)
        {
            is_left = OwO;

            if (is_left)
                x_pos = -FRAME_SMOKELEFT_WIDTH;

            else x_pos = SCREEN_WIDTH;

            y_pos = 0;
        }

        void Update_Position()
        {
            if (is_left)
            {
                if (x_pos >= SCREEN_WIDTH)
                    x_pos = -FRAME_SMOKELEFT_WIDTH;

                else x_pos += 2;
            }
            else
            {
                if (x_pos <= -FRAME_SMOKERIGHT_WIDTH)
                    x_pos = SCREEN_WIDTH;

                else x_pos -= 2;
            }
        }

        void render()
        {
            if (is_left)
                loadFromFile("menu/smoke_left.png");

            else loadFromFile("menu/smoke_right.png");

            SDL_Rect renderquad = {x_pos, y_pos, mWidth, mHeight};

            SDL_RenderCopy(gRenderer, mTexture, NULL, &renderquad);

            Update_Position();
        }

        // void HandleInputAction();

    private:

        int x_pos, y_pos;

        bool is_left;
};

class Menu: public BaseObject
{
    public:
        Menu();
        ~Menu();

        void HandleInputAction(SDL_Event e);

        void render();

        bool playing();

    private:

        Mix_Chunk* intro;

        bool is_playing;

        bool is_updateSmoke;

        bool is_intro1;

        Smoke smoke_left, smoke_right;
};

