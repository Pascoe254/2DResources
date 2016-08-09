#include "turret.h"

Turret::Turret(SDL_Renderer *renderer, string filePath, string audioPath, float x, float y) {
	active = true;

	string turretPath = filePath + "turret.png";

	texture = IMG_LoadTexture(renderer, turretPath.c_str());


	health = 3;

	posRect.w = 200;
	posRect.h = 500;

	posRect.x = x;
	posRect.y = y;

	string bulletPath = filePath + "turretbullet.png";

	for (int i = 0; i < 10; i++)
	{
		TurretBullet tmpBullet(renderer, bulletPath, 5000, 500000);

		bulletList.push_back(tmpBullet);
	}
	srand(time(NULL));

	pos_X = posRect.x;
	pos_Y = posRect.y;
}

void Turret::TankMoveX(float playerSpeed, float deltaTime) {
	pos_X += (playerSpeed)* deltaTime;
	
	posRect.x = (int)(pos_X + .5f);	
}

void Turret::TankMoveY(float playerSpeed, float deltaTime) {
	pos_Y += (playerSpeed)* deltaTime;

	posRect.y = (int)(pos_Y + .5f);
}

void Turret::Draw(SDL_Renderer *renderer)
{
	if (active) {
		for (int i = 0; i < bulletList.size(); i++)
		{
			if (bulletList[i].active) {
				bulletList[i].Draw(renderer);
			}

		}

		SDL_RenderCopy(renderer, texture, NULL, &posRect);

	}

}

void Turret::CreateBullet(SDL_Rect target)
{
	for (int i = 0; i < bulletList.size(); i++) {
		if (bulletList[i].active == false) {

			bulletList[i].Start(target, posRect);

			bulletList[i].active = true;

			bulletList[i].posRect.x = ((posRect.x + (posRect.w / 2)) - (bulletList[i].posRect.w / 2));
			bulletList[i].posRect.y = ((posRect.y + (posRect.h / 2)) - (bulletList[i].posRect.h / 2));

			bulletList[i].pos_X = bulletList[i].posRect.x;
			bulletList[i].pos_Y = bulletList[i].posRect.y;


			break;
		}
	}
}

void Turret::Update(float deltaTime, SDL_Rect playerRect) {

	if (active) {
		x = (playerRect.x + (playerRect.w / 2)) - (posRect.x + (posRect.w / 2));
		y = (playerRect.y + (playerRect.h / 2)) - (posRect.y + (posRect.h / 2));
		
		if (SDL_GetTicks() > firetime) {

			if (posRect.x> 0 && posRect.x < 1024 && posRect.y > 0 && posRect.y < 768) {
				CreateBullet(playerRect);
			}
			firetime = SDL_GetTicks() + (rand() % 3 + 1) * 1000;

		}



		for (int i = 0; i < bulletList.size(); i++) {
			if (bulletList[i].active) {
				bulletList[i].Update(deltaTime);
			}
		}
	}

	if (health < 1) {
		active = false;
	}
}