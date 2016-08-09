#include <string>
#include <iostream>

using namespace std;
#include <vector>

#if defined(__APPLE__)
#include <SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>

#endif


#if defined(_WIN32) || (_WIN64)

#include "SDL.h"
#include "SDL_image.h"
#endif
#include <time.h>

#include "turretbullet.h"

class Turret {
public:
	bool active;

	vector<TurretBullet> bulletList;

	string turretPath;

	SDL_Texture *texture;

	SDL_Rect posRect;

	float x, y,pos_X,pos_Y;

	float firetime = 0.0f;
	float fireRate = 1000.0f;

	int health;

	void TankMoveX(float tankSpeed, float deltaTime);

	void TankMoveY(float tankSpeed, float deltaTime);

	Turret(SDL_Renderer *renderer, string filePath, string audioPath, float x, float y);

	void Update(float deltaTime, SDL_Rect playerRect);

	void Draw(SDL_Renderer* renderer);


	void CreateBullet(SDL_Rect target);

};
