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
#include <string.h>
#include "player.h"
#include "pickup.h"

using namespace std;

float deltaTime = 0.0;
int thistime = 0;
int lasttime = 0;

float x_pos = 0.0, y_pos = 0.0;

//source file declarations
#if defined(__APPLE__)


string currentWorkingDirectory(getcwd(NULL,0));

string images_dir = currentWorkingDirectory +"/2DResources/images/";

string audio_dir = currentWorkingDirectory + "/audio/";
#endif

#if defined(_WIN32) || (_WIN64)
#include <direct.h>

string s_cwd(_getcwd(NULL, 0));

//create a string linking to the mac's image folder
string images_dir = s_cwd + "\\2DResources\\images\\";

string audio_dir = s_cwd + "\\2DResources\\audio\\";
#endif

bool quit,menu,game,win,lose;
enum GameState {
		MENU, GAME,WIN, LOSE
	};

GameState gameState = GAME;



int main(int argc, char* argv[]) {

    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2

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
	//SDL_Surface *surface = IMG_Load(BKGDpath.c_str());

	//create a SDL texture

	SDL_Texture *bkgd1;

	//place surface info into the texture background

	bkgd1 = IMG_LoadTexture(renderer, BKGDpath.c_str());

	if (bkgd1 == NULL)
	{
		
		cout << "texture is blank";
	}

	SDL_Rect bkgd1pos;
	bkgd1pos.x = 0;
	bkgd1pos.y = -768;
	bkgd1pos.w = 3072;
	bkgd1pos.h = 2314;

	Player player1 = Player(renderer,images_dir,audio_dir,100,600);
	Pickup orb1 = Pickup(renderer,1,images_dir,audio_dir,160,600);
	Pickup orb2 = Pickup(renderer,1, images_dir, audio_dir, 230, 600);
	Pickup orb3 = Pickup(renderer,1, images_dir, audio_dir, 300, 600);

	SDL_Rect EnemyRect;
	EnemyRect.x = 400;
	EnemyRect.y = 600;
	EnemyRect.w = 64;
	EnemyRect.h = 64;

	SDL_Texture * testenemy;

	string enemypath = images_dir + "testenemy.png";

	testenemy = IMG_LoadTexture(renderer, enemypath.c_str());
	
    SDL_Event event;

  //  SDL_Surface* screenSurface = NULL;

    //screenSurface = SDL_GetWindowSurface(window);

    //SDL_FillRect(screenSurface, NULL, SDL_MapRGB( screenSurface->format,0,42,254));

    //SDL_UpdateWindowSurface(window);

    // The window is open: could enter program loop here (see SDL_PollEvent())
    while(!quit){

		thistime = SDL_GetTicks();
		deltaTime = (float)(thistime - lasttime) / 1000;
		lasttime = thistime;
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
						quit = true;
    					break;
    				}
    			}
    		}
    		break;
    	case GAME:
    		game = true;
    		while(game){
    			game = true;
    			
    			if(SDL_PollEvent(&event)){
					if(event.type == SDL_QUIT){
						quit = true;
						game = false;
						break;
					}

					if(event.type == SDL_KEYUP){
						player1.release(event);
					}
					if(event.type == SDL_KEYDOWN){
						player1.press(event);
					}

					switch(event.key.keysym.sym){


					case SDLK_w:

						if(!player1.playerjump){
						player1.playerjump = true;
						player1.jumpcount=-100;
						}

						break;
					case SDLK_s:
						player1.movebdown = true;
						y_pos = bkgd1pos.y;
						y_pos -= (player1.speed)*deltaTime;
						bkgd1pos.y = (int)(y_pos + 0.5f);
						if (bkgd1pos.y < -1536) {
							bkgd1pos.y = -1536;
							y_pos = -1536;
						}

						player1.movebdown = false;

						break;
					case SDLK_SPACE:
     						player1.ammo();

						
						break;

					}
				}


    			SDL_RenderClear(renderer);

				if (player1.posRect.x >= 800 - player1.posRect.w && player1.movebright) {
					x_pos -= (player1.speed)*deltaTime;
					bkgd1pos.x = (int)(x_pos + 0.5f);
					player1.movebright = false;

					if (bkgd1pos.x < -2048) {
						bkgd1pos.x = -2048;
						x_pos = -2048;
					}
				}

				if (player1.posRect.x <= 100 && player1.movebleft) {
					x_pos += (player1.speed)*deltaTime;
					bkgd1pos.x = (int)(x_pos + 0.5f);
					player1.movebleft = false;

					if (bkgd1pos.x > 0) {
						bkgd1pos.x = 0;
						x_pos = 0;
					}
				}

				if (SDL_HasIntersection(&player1.posRect, &orb1.pickupRect) && orb1.active) {
					player1.orb1 = true;
					orb1.active = false;
				}

				if (SDL_HasIntersection(&player1.posRect, &orb2.pickupRect) && orb2.active) {
					player1.orb2 = true;
					orb2.active = false;
				}

				if (SDL_HasIntersection(&player1.posRect, &orb3.pickupRect) && orb3.active) {
					player1.orb3 = true;
					orb3.active = false;
				}

				if (SDL_HasIntersection(&player1.posRect, &EnemyRect)) {
					player1.health();
				}


				//draw the background
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1pos);

				SDL_RenderCopy(renderer, testenemy, NULL, &EnemyRect);

				player1.Draw(renderer);

				player1.Update(deltaTime);

				orb1.draw(renderer);
				orb2.draw(renderer);
				orb3.draw(renderer);

				if(player1.playerjump){
					player1.jump();
				}

				

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
