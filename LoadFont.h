#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"

class Font : public BaseObject
{
    public:
        Font();
        ~Font();
        void SetFont(TTF_Font* font);
        bool loadFromRenderedText(string textureText, SDL_Color textColor);
        void render(int x, int y);
    private:
        TTF_Font *gFont;
};

