#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"
#include "LoadFont.h"
#include "LoadFont.cpp"

class Score 
{
    private:
        Font score_displayed, num_die_displayed;

        //Điểm tổng
        int score;

        //Phục vụ cho việc nhân hệ số từng loop
        int num_die, score_loop;

        //Dành cho việc hiển thị của num_die_displayed dài tương đối -> Không bị ngắn quá do fps tương đối nhanh
        int frame = 0;

    public:

        Score();
        ~Score();

        void SetFont();

        string Convert(int a);

        void Update_ScoreLoop(int a);

        void Update_Score();

        int get_die();

        void render();

        int get_score();
};