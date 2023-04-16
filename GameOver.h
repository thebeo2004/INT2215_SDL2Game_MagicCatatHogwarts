#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"
#include "LoadFont.h"
#include "LoadFont.cpp"

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

    private:

        Font score_displaying, result_displaying;

        bool is_victory;
};