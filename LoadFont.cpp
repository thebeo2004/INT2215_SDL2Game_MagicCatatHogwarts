#pragma once

#include "LoadFont.h"

Font::Font()
{
}

Font::~Font()
{
    free();
}

void Font::SetFont(TTF_Font* font)
{
    gFont = font;
}

bool Font::loadFromRenderedText(string textureText, SDL_Color textColor)
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont_threat, textureText.c_str(), textColor);

    if (textSurface == NULL)
        cout << "Unable to render text surface! " << TTF_GetError() << "\n";
    else
    {
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

        if (mTexture == NULL)
            cout << "Unable to create texture from rendered text! " << SDL_GetError() << "\n";
        
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }

    return mTexture != NULL;
}

void Font::render(int x, int y)
{
    SDL_Rect renderquad = {x, y, mWidth, mHeight};
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderquad);
}
