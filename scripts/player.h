#if defined(__APPLE__)
#include <SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<SDL2_mixer/SDL_mixer.h>
#include<SDL2_ttf/SDL_ttf.h>
#endif

#if defined(_WIN32) || (_WIN64)

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#endif

#include<string>
#include<iostream>
#include<sstream>
#include<vector>

using namespace std;

class Player{
public:


	SDL_Rect posRect;
	float speed, pos_X;
	SDL_Texture * texture;


	Player(SDL_Renderer *renderer, string imagePath, string audioPath, float x, float y);

	void Update(float deltaTime);

	void Draw(SDL_Renderer *renderer);

	void moveright(float timedelta);

	void moveleft(float timedelta);


};
