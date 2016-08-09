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

class Pickup {
public:
	int identifier;
	SDL_Rect pickupRect;
	SDL_Texture * Tex;

	bool active;
	
	
	Pickup(SDL_Renderer *renderer,int iden,string imagepath, string audiopath, float x, float y);

	void draw(SDL_Renderer * renderer);
};