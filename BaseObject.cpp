#pragma once
#include "BaseObject.h"

BaseObject::BaseObject()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

BaseObject::~BaseObject()
{
    free();
}

void BaseObject::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
        
    }
}

bool BaseObject::loadFromFile(string path)
{
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
        cout << "Unable to load IMG\n";
    
    // SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));

    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

    if (newTexture != NULL)
    {
        mWidth = loadedSurface->w;
        mHeight = loadedSurface->h;
    }

    SDL_FreeSurface(loadedSurface);

    mTexture = newTexture;

    return (mTexture != NULL);
}

void BaseObject::render(int x, int y, SDL_Rect* clip)
{
    SDL_Rect renderquad;
    renderquad = {x, y, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderquad);
}

int BaseObject::getWidth()
{
    return mWidth;
}

int BaseObject::getHeight()
{
    return mHeight;
}