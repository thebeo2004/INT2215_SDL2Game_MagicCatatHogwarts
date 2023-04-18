//@Author: Nguyen Huu The aka Ca_Uop_Muoi
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BaseObject.cpp"
#include "MainObject.h"
#include "MainObject.cpp"
#include "ImpTimer.h"
#include "ImpTimer.cpp"
#include "ThreatsObject.h"
#include "ThreatsObject.cpp"
#include "LoadFont.h"
#include "LoadFont.cpp"
#include "Score.h"
#include "Score.cpp"
#include "Support.h"
#include "Support.cpp"
#include "Menu.h"
#include "Menu.cpp"
#include "GameOver.h"
#include "GameOver.cpp"

bool init();
bool loadMedia();
void close();

BaseObject gBackground;
MainObject character;

vector<vector<ThreatsObject>> threats(9);

vector<int> v = {2500, 5000, 7500, 9500, 12000, 16000, 21000, 25000, 30000};

//BGM of game
Mix_Music *BGM = NULL;



//Score of gaming process
Score score;

//Heal mạng cho main
Support life_4th(SCREEN_WIDTH - 80, SCREEN_HEIGHT/2 - 20, 4);
Support life_2th(SCREEN_WIDTH - 80, 75, 2);

Menu menu;

//Hien thi ket thuc
Over the_end;

bool init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    gWindow = SDL_CreateWindow("Magic-Cat-at-Hogwarts, @Author: Nguyen Huu The aka Ca_Uop_Muoi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
        return false;
    
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL)
        return false;

    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) && imgFlags))
        return false;

    if (TTF_Init() == -1)
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		return false;
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 3, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
	}
    
    return true;
}

bool loadMedia()
{
    bool success = true;

    //load image
    if (!(character.loadFromFile("character/running.png") && gBackground.loadFromFile("background/background.png")))
    {
        cout << "Cannot load Img\n";
        success = false;
    }
    else
    {
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < int(threats[i].size()); j++)
            {
                if (!threats[i][j].loadFromFile("threats/normal_left.png"))
                {
                    cout << "Cannot load threat images\n";
                    success = false;
                }
                threats[i][j].set_clips();
            }
        }

        character.set_clips();
    }

    //Load music and sound effect of threats
	BGM = Mix_LoadMUS( "sound/BGM.ogg" );

    sound_threat_effect = Mix_LoadWAV("sound/threat_die.ogg");

	if( BGM == NULL | sound_threat_effect == NULL)
	{
		printf( "Failed to load beat music && threats effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

    //Load font
    gFont_22 = TTF_OpenFont("font/default.ttf", 22);
    gFont_40 = TTF_OpenFont("font/default.ttf", 40);
    gFont_38 = TTF_OpenFont("font/default.ttf", 38);
    if (gFont_22 == NULL || gFont_40 == NULL || gFont_38 == NULL)
    {
        cout << "Failed to load lazy font! " << TTF_GetError() << "\n";
        success = false;
    }

    return success;
}

void close()
{
    TTF_CloseFont(gFont_22);
    TTF_CloseFont(gFont_38);
    TTF_CloseFont(gFont_40);
    gFont_40 = NULL;
    gFont_22 = NULL;
    gFont_38 = NULL;

    Mix_FreeMusic(BGM);
    Mix_FreeChunk(sound_threat_effect);
    BGM = NULL;
    sound_threat_effect = NULL;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
}

void Resize_ThreatsList()
{
    threats[0].resize(1);
    threats[1].resize(5);
    threats[2].resize(7);
    threats[3].resize(7);
    threats[4].resize(7);
    threats[5].resize(8);
    threats[6].resize(9);
    threats[7].resize(10);
    threats[8].resize(12);
}

void Initialize_Threats()
{
    for(int i = 0; i < 9; i++)
    {
        if (i == 0) threats[0][0].setPos(646, 276);

        else
        {
            for(int j = 0; j < int(threats[i].size()); j++)
            {
                pair<int, int> cur = RANDOM_POSITION[rand() % 28];

                threats[i][j].setPos(cur.first, cur.second);
            }
        }
    }
}

int main(int argc, char * args[])
{
    srand(time(0));

    Resize_ThreatsList();

    if (!init()) return -1;
    if (!loadMedia()) return -1;

    Initialize_Threats();

    SDL_Event e;

    bool is_playingBGM = false;
    // Mix_PlayMusic(BGM, -1);

    score.SetFont();
    
    int batch = 0;

    ImpTimer timer;
    int time_one_frame = 1000/FRAME_PER_SECOND;

    life_4th.set_clips();
    life_2th.set_clips();

    the_end.SetFont();

    bool free_after_game = false;

    while(true)
    {
        timer.start();

        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);

        if (!menu.playing())
        {
            if (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT) break;

                menu.HandleInputAction(e);
            }

            menu.render();
            
            time_start_playing = SDL_GetTicks();
        }
        else if (!character.is_gameover())
        {
            if (!is_playingBGM && SDL_GetTicks() - time_start_playing >= 1500)
                Mix_PlayMusic(BGM, -1),
                is_playingBGM = true;

            gBackground.render(0, 0, NULL);

            if (batch <= 8 && SDL_GetTicks() - time_start_playing >= v[batch]) batch++;

            life_4th.check_Displaying(character.get_LifePoint());
            life_2th.check_Displaying(character.get_LifePoint());

            if (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT) break;

                character.HandelInputAction(e);

                if (life_4th.HandleInputAction(e)) character.Heal();
                if (life_2th.HandleInputAction(e)) character.Heal();

                for(int i = 0; i < batch; i++)
                {
                    for(int j = 0; j < int(threats[i].size()); j++)
                    {
                        threats[i][j].HandleInputAction(e);
                    }
                }
            }

            //check collision
            for(int i = 0; i < batch; i++)
            {
                for(int j = 0; j < int(threats[i].size()); j++)
                {
                    if (isCollision(character.getReal_Position(), threats[i][j].getReal_Position()))
                    {
                        character.hurt();

                        threats[i][j].attack();
                    }

                    if (character.check_lightning())
                        threats[i][j].Lightning();
                    
                    if (character.check_sunken())
                        threats[i][j].Sunken();

                    score.Update_ScoreLoop(threats[i][j].GetScore(character.getReal_Position()));
                    threats[i][j].render();
                }
            }

            character.Count_ThreatsDie(score.get_die());

            character.render();

            life_4th.render();
            life_2th.render();

            score.render();

            if (num_threats_disappear == TOTAL_THREATS) character.victory();
        }
        else if (character.is_gameover())
        {
            if (!free_after_game)
            { 
                Mix_HaltMusic();
                
                for(int i = 0; i < 9; i++)
                {
                    for(int j = 0; j < int(threats[i].size()); j++)
                        threats[i][j].free();
                }
                free_after_game = true;
            }

            if (SDL_PollEvent(&e) != 0)
                if (e.type == SDL_QUIT) break;

            if (character.get_LifePoint() > 0)
                the_end.victory(score.get_score());
            else the_end.lose();

            the_end.render();
        }

        SDL_RenderPresent(gRenderer);

        int imp_time_real = timer.get_ticks();

        if (imp_time_real < time_one_frame) SDL_Delay(time_one_frame - imp_time_real);
    }

    close();
}
