#include "turretBullet.h"

TurretBullet::TurretBullet(SDL_Renderer *renderer, string filePath, float x, float y) {
	active = false;

	speed = 2.0;

	texture = IMG_LoadTexture(renderer, filePath.c_str());

	int w, h;

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	posRect.w = w;
	posRect.h = h;

	posRect.x = x;
	posRect.y = y;

	pos_X = x;
	pos_Y = y;
}

void TurretBullet::Start(SDL_Rect playerPos, SDL_Rect turretPos) {

	player.x = playerPos.x + (playerPos.w/2);
	player.y = playerPos.y + (playerPos.h/2);

	turret.x = turretPos.x + (turretPos.w/2);
	turret.y = turretPos.y + (turretPos.h/2);

	distance = sqrt((player.x - turret.x) * (player.x - turret.x) + (player.y - turret.y) * (player.y - turret.y));
}

void TurretBullet::Reset()
{
	//posRect.x = -10000;
	pos_X = posRect.x;

	active = false;

}

void TurretBullet::Draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, NULL, &posRect);
}

void TurretBullet::Update(float deltaTime) {
	float vX = ((player.x) - turret.x) / distance;
	float vY = ((player.y) - turret.y) / distance;

	pos_X += (vX * speed * deltaTime);
	pos_Y += (vY * speed * deltaTime);

	posRect.x = (int)(pos_X + 0.5f);
	posRect.y = (int)(pos_Y + 0.5f);

	//cout << posRect.x << "-" << posRect.y << "\n";

	if ((posRect.y < (0 - posRect.h)) || (posRect.y > 768) || (posRect.x < (0 - posRect.w)) || (posRect.x>1024)) {
		Reset();
	}

}
