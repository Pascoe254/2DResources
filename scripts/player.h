#if defined(__APPLE__)
#include <SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<SDL2_mixer/SDL_mixer.h>
#include<SDL2_ttf/SDL_ttf.h>
#endif

#if defined(_WIN32) || (_WIN64)

#include "SDL.h"
#include "SDL_image.h"

#endif

#include<string>
#include<iostream>
#include<sstream>
#include<vector>

using namespace std;

class Player{
public:


	SDL_Rect posRect, backH, midH, frontH , backa, fronta,puback,pu1,pu2,pu3;
	float speed, pos_X,pos_Y,firetime,hittime,jumppos;
	SDL_Texture * texture,*backhealth,*fronthealth,*backammo,*frontammo,*backorbs1, *backorbs2, *backorbs3,*frontorbs, *midhealth;

	int damage, maxhealth, ammoused,jumpcount,normaly;
	bool movebup, movebdown, movebleft, movebright, orb1, orb2, orb3,shoot,hit,playerjump,movepright,movepleft;


	Player(SDL_Renderer *renderer, string imagePath, string audioPath, float x, float y);

	void Update(float timedelta);

	void Draw(SDL_Renderer *renderer);

	void moveright(float timedelta);

	void moveleft(float timedelta);

	void ammo();

	void health();

	void jump();

	void release(SDL_Event event);

	void press(SDL_Event event);
};
