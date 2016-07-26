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

using namespace std;

//source file declarations
#if defined(__APPLE__)

string currentWorkingDirectory(getcwd(NULL,0));

string images_dir = currentWorkingDirectory +"/images/";

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

GameState gameState = MENU;



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

    SDL_Event event;

    SDL_Surface* screenSurface = NULL;

    screenSurface = SDL_GetWindowSurface(window);

    SDL_FillRect(screenSurface, NULL, SDL_MapRGB( screenSurface->format,0,42,254));

    SDL_UpdateWindowSurface(window);

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
    				case SDLK_p:
    					quit = true;
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
    			if(SDL_PollEvent(&event)){
					if(event.type == SDL_QUIT){
						quit = true;
						game = false;
						break;
					}
					switch(event.key.keysym.sym){
					case SDLK_p:
						quit = true;
						game = false;
						break;
					case SDLK_d:
						quit = true;
						game = false;
						break;

					}
				}
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
