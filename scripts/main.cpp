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
<<<<<<< HEAD
#include "turret.h"
=======
>>>>>>> origin/master

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

	string fallpath = images_dir + "test.png";


	//create a SDL texture

	SDL_Texture *fall;

	//place surface info into the texture background

	fall = IMG_LoadTexture(renderer, fallpath.c_str());


	SDL_Rect fallpos;
	fallpos.x = bkgd1pos.x + 800;
	fallpos.y =  bkgd1pos.y + 1450;
	fallpos.w = 120;
	fallpos.h = 900;

	SDL_Rect climbpos;
	climbpos.x = bkgd1pos.x + 2150;
	climbpos.y =  bkgd1pos.y + 800;
	climbpos.w = 120;
	climbpos.h = 2000;

	string boundspath = images_dir + "bounds.png";
	//create a SDL texture

	SDL_Texture *bounds;

	//place surface info into the texture background

	bounds = IMG_LoadTexture(renderer, boundspath.c_str());


	SDL_Rect boundspos1;
	boundspos1.x = bkgd1pos.x;
	boundspos1.y =  bkgd1pos.y + 1450;
	boundspos1.w = 735;
	boundspos1.h = 768;

	SDL_Rect boundspos2;
	boundspos2.x = bkgd1pos.x + 980;
	boundspos2.y =  bkgd1pos.y + 768;
	boundspos2.w = 1100;
	boundspos2.h = 1200;

	SDL_Rect boundspos3;
	boundspos3.x = bkgd1pos.x + 2400;
<<<<<<< HEAD
	boundspos3.y =  bkgd1pos.y + 1000;
	boundspos3.w = 1100;
	boundspos3.h = 1200;

	Player player1 = Player(renderer,images_dir,audio_dir,100,550);
=======
	boundspos3.y =  bkgd1pos.y + 768;
	boundspos3.w = 1100;
	boundspos3.h = 1200;

	Player player1 = Player(renderer,images_dir,audio_dir,100,600);
>>>>>>> origin/master
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
<<<<<<< HEAD

	Turret turret1 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 500.0f, 200.0f);
=======
>>>>>>> origin/master
	
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
<<<<<<< HEAD
					//turret1.TankMoveX(-player1.speed, deltaTime);
=======
>>>>>>> origin/master
					player1.movebright = false;

					if (bkgd1pos.x < -2048) {
						bkgd1pos.x = -2048;
						x_pos = -2048;
					}

					climbpos.x = bkgd1pos.x + 2150;
					fallpos.x = bkgd1pos.x + 800;
					boundspos1.x = bkgd1pos.x;
					boundspos2.x = bkgd1pos.x+980;
					boundspos3.x = bkgd1pos.x+2400;
<<<<<<< HEAD
					turret1.posRect.x = bkgd1pos.x+500;
=======
>>>>>>> origin/master
				}

				if (player1.posRect.x <= 100 && player1.movebleft) {
					x_pos += (player1.speed)*deltaTime;
<<<<<<< HEAD
				//	turret1.TankMoveX(player1.speed, deltaTime);
=======
>>>>>>> origin/master
					bkgd1pos.x = (int)(x_pos + 0.5f);
					player1.movebleft = false;

					if (bkgd1pos.x > 0) {
						bkgd1pos.x = 0;
						x_pos = 0;
					}

					climbpos.x = bkgd1pos.x + 2150;
					fallpos.x = bkgd1pos.x + 800;
					boundspos1.x = bkgd1pos.x;
					boundspos2.x = bkgd1pos.x+980;
					boundspos3.x = bkgd1pos.x+2400;
<<<<<<< HEAD
					turret1.posRect.x = bkgd1pos.x+500;
=======

>>>>>>> origin/master
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
				if (SDL_HasIntersection(&player1.posRect, &boundspos1)&& player1.posRect.y > boundspos1.y) {
					player1.posRect.x=boundspos1.x+736;
					player1.pos_X = player1.posRect.x;
				}

				if (SDL_HasIntersection(&player1.posRect, &boundspos2)&& player1.posRect.y + player1.posRect.h < boundspos2.y + boundspos2.h && player1.posRect.x < boundspos2.x) {
					player1.posRect.x=boundspos2.x - player1.posRect.w;
					player1.pos_X = player1.posRect.x;
				}

				if (SDL_HasIntersection(&player1.posRect, &boundspos2)&& player1.posRect.y + player1.posRect.h < boundspos2.y + boundspos2.h && player1.posRect.x > boundspos2.x) {
					player1.posRect.x=boundspos2.x + boundspos2.w;
					player1.pos_X = player1.posRect.x;
				}

<<<<<<< HEAD
				if (SDL_HasIntersection(&player1.posRect, &boundspos3)&& player1.posRect.x < boundspos3.x) {
					player1.posRect.x = boundspos3.x - player1.posRect.w;
					player1.pos_X = player1.posRect.x;
				}

				for (int i = 0; i < turret1.bulletList.size(); i++) {
					if (SDL_HasIntersection(&player1.posRect, &turret1.bulletList[i].posRect) && turret1.active && &turret1.bulletList[i].active) {
						turret1.bulletList[i].Reset();
						player1.health();
						break;
					}
				}

				for (int i = 0; i < player1.bulletList.size(); i++) {
					if (SDL_HasIntersection(&turret1.posRect, &player1.bulletList[i].posRect) && turret1.active && &player1.bulletList[i].active) {
						player1.bulletList[i].Reset();
						turret1.health--;
						break;
					}
				}


				if (SDL_HasIntersection(&player1.posRect, &fallpos)) {
					player1.movebdown = true;
					player1.posRect.y = player1.normaly = 575;

					boundspos1.y =  bkgd1pos.y + 1450;
					boundspos2.y =  bkgd1pos.y + 500;
					boundspos3.y = bkgd1pos.y+1000;
=======
				if (SDL_HasIntersection(&player1.posRect, &fallpos)) {
					player1.movebdown = true;
					player1.posRect.y = player1.normaly = 650;

					boundspos1.y =  bkgd1pos.y + 1450;
					boundspos2.y =  bkgd1pos.y + 500;
					boundspos3.y = bkgd1pos.y+800;
>>>>>>> origin/master
					climbpos.y = bkgd1pos.y + 1000;
				}

				if (SDL_HasIntersection(&player1.posRect, &climbpos)) {
					player1.movebup = true;
<<<<<<< HEAD
					player1.posRect.y = player1.normaly = 575;

					boundspos1.y =  bkgd1pos.y + 1450;
					boundspos2.y =  bkgd1pos.y + 500;
					boundspos3.y = bkgd1pos.y+1000;
=======
					player1.posRect.y = player1.normaly = 650;

					boundspos1.y =  bkgd1pos.y + 1450;
					boundspos2.y =  bkgd1pos.y + 500;
					boundspos3.y = bkgd1pos.y+800;
>>>>>>> origin/master
					climbpos.y = bkgd1pos.y + 1000;
				}


				if(player1.movebdown){
				y_pos = bkgd1pos.y;
				y_pos -= (player1.speed)*deltaTime;
<<<<<<< HEAD
				//turret1.TankMoveY(-player1.speed/2, deltaTime);

=======
>>>>>>> origin/master
				bkgd1pos.y = (int)(y_pos + 0.5f);
				if (bkgd1pos.y < -1536) {
					bkgd1pos.y = -1536;
					y_pos = -1536;
					player1.movebdown = false;
					}
				}

				if(player1.playerjump & !player1.movebup){
					player1.jump();
				}

				if(player1.movebup && player1.climb){
				y_pos = bkgd1pos.y;
				y_pos += (player1.speed/2)*deltaTime;
<<<<<<< HEAD
				//turret1.TankMoveY(player1.speed/2, deltaTime);
=======
>>>>>>> origin/master
				bkgd1pos.y = (int)(y_pos + 0.5f);
				if (bkgd1pos.y > 0) {
					bkgd1pos.y = 0;
					y_pos = 0;
					player1.movebup = false;
<<<<<<< HEAD
					player1.posRect.y = player1.normaly = 575;
=======
					player1.posRect.y = player1.normaly = 590;
>>>>>>> origin/master

					}
				}




//				if (bkgd1pos.y == 0 && bkgd1pos.x != -2048) {
//
//					x_pos -= (player1.speed)*deltaTime;
//					bkgd1pos.x = (int)(x_pos + 0.5f);
//					if (bkgd1pos.x < -2048) {
//						bkgd1pos.x = -2048;
//						x_pos = -2048;
//						player1.posRect.x=100;
//						player1.pos_X = player1.posRect.x;
//					}
//   			}
				player1.Update(deltaTime);
<<<<<<< HEAD
				turret1.Update(deltaTime, player1.posRect);
=======

>>>>>>> origin/master

				//draw the background
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1pos);

				SDL_RenderCopy(renderer, testenemy, NULL, &EnemyRect);
				SDL_RenderCopy(renderer, fall, NULL, &climbpos);
				//SDL_RenderCopy(renderer, bounds, NULL, &boundspos1);
				SDL_RenderCopy(renderer, bounds, NULL, &boundspos3);

				player1.Draw(renderer);
<<<<<<< HEAD
				turret1.Draw(renderer);
=======

>>>>>>> origin/master


				orb1.draw(renderer);
				orb2.draw(renderer);
				orb3.draw(renderer);



				

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
