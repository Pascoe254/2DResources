#if defined(__APPLE__)
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#endif

#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#endif

#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include "player.h"

using namespace std;

float deltaTime = 0.0;
int thistime = 0;
int lasttime = 0;

//source file declarations
#if defined(__APPLE__)

string currentWorkingDirectory(getcwd(NULL,0));

string images_dir = currentWorkingDirectory +"/2DResources/images/";

string audio_dir = currentWorkingDirectory + "/audio/";
#endif

#if defined(_WIN32) || (_WIN64)


string s_cwd(getcwd(NULL, 0));

//create a string linking to the mac's image folder
string images_dir = s_cwd + "\\images\\";

string audio_dir = s_cwd + "\\audio\\";
#endif

bool quit,menu,game,win,lose;
enum GameState {
		MENU, GAME,WIN, LOSE
	};

GameState gameState = GAME;



int main(int argc, char* argv[]) {

    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        1024,                               // width, in pixels
        768,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = NULL;

	//create the renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//**********Create background image********
	string BKGDpath = images_dir + "primary.png";

	//create a SDL Surface to hold the background image
	SDL_Surface *surface = IMG_Load(BKGDpath.c_str());

	//create a SDL texture

	SDL_Texture *bkgd1;

	//place surface info into the texture background
	bkgd1 = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect bkgd1pos;
	bkgd1pos.x = 0;
	bkgd1pos.y = -768;
	bkgd1pos.w = 3072;
	bkgd1pos.h = 2314;

	Player player1 = Player(renderer,images_dir,audio_dir,100,600);


    SDL_Event event;

  //  SDL_Surface* screenSurface = NULL;

    //screenSurface = SDL_GetWindowSurface(window);

    //SDL_FillRect(screenSurface, NULL, SDL_MapRGB( screenSurface->format,0,42,254));

    //SDL_UpdateWindowSurface(window);

    // The window is open: could enter program loop here (see SDL_PollEvent())
    while(!quit){
    	switch(gameState){
    	case MENU:
    		menu = true;

    		while(menu){

    			if(SDL_PollEvent(&event)){
    				if(event.type == SDL_QUIT){
    					quit = true;
    					menu = false;
    					break;
    				}
    				switch(event.key.keysym.sym){
    				case SDLK_d:
    					menu = false;
    					break;
    				}
    			}
    		}
    		break;
    	case GAME:
    		game = true;
    		while(game){
    			game = true;
    			thistime = SDL_GetTicks();
				deltaTime = (float)(thistime - lasttime) / 1000;
				lasttime = thistime;
    			if(SDL_PollEvent(&event)){
					if(event.type == SDL_QUIT){
						quit = true;
						game = false;
						break;
					}
					switch(event.key.keysym.sym){
					case SDLK_d:
						player1.moveright(deltaTime);
						break;
					case SDLK_a:
						player1.moveleft(deltaTime);
						break;

					}
				}



    			SDL_RenderClear(renderer);

				//draw the background
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1pos);

				player1.Draw(renderer);

				SDL_RenderPresent(renderer);


    		}

    		break;

    	}
    }
    //end of loop while


    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}
