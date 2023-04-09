#include "CommonFunc.h"
#include "BaseObject.h"
#include "BaseObject.cpp"
#include "MainObject.h"
#include "MainObject.cpp"
#include "ImpTimer.h"
#include "ImpTimer.cpp"
#include "ThreatsObject.h"
#include "ThreatsObject.cpp"

bool init();
bool loadMedia();
void close();

BaseObject gBackground;
MainObject character;

vector<vector<ThreatsObject>> threats(9);

vector<int> v = {2500, 5000, 7500, 9500, 12000, 16000, 21000, 25000, 30000};

//BGM of game
Mix_Music *BGM = NULL;

bool init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    gWindow = SDL_CreateWindow("Ca_Uop_Muoi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 4, 2048 ) < 0 )
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

    //Load music
	BGM = Mix_LoadMUS( "sound/BGM.ogg" );
	if( BGM == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

    //Load font
    gFont_threat = TTF_OpenFont("font/default.ttf", 22);
    if (gFont_threat == NULL)
    {
        cout << "Failed to load lazy font! " << TTF_GetError() << "\n";
        success = false;
    }

    return success;
}

void close()
{
    character.free();
    gBackground.free();

    TTF_CloseFont(gFont_threat);
    gFont_threat = NULL;

    Mix_FreeMusic(BGM);
    BGM = NULL;

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
    threats[1].resize(1);
    threats[2].resize(5);
    threats[3].resize(5);
    threats[4].resize(5);
    threats[5].resize(6);
    threats[6].resize(6);
    threats[7].resize(7);
    threats[8].resize(8);
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

    ImpTimer timer;
    int time_one_frame = 1000/FRAME_PER_SECOND;

    Mix_PlayMusic(BGM, -1 );
    
    int batch = 0;

    while(true)
    {
        timer.start();

        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);

        gBackground.render(0, 0, NULL);

        if (batch <= 8 && SDL_GetTicks() >= v[batch]) batch++;

        if (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) break;

            character.HandelInputAction(e);

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
                
                threats[i][j].render();
            }
        }

        character.render();

        SDL_RenderPresent(gRenderer);

        int imp_time_real = timer.get_ticks();

        if (imp_time_real < time_one_frame) SDL_Delay(time_one_frame - imp_time_real);
        
    }

    close();
}
