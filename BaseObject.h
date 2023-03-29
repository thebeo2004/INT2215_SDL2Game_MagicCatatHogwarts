#pragma once

#include "CommonFunc.h"

class BaseObject
{
    public:
        BaseObject();
        ~BaseObject();
        bool loadFromFile(string path);
        void free();
        void render(int x, int y, SDL_Rect* clip);
        int getWidth();
        int getHeight();
    protected:
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;
};