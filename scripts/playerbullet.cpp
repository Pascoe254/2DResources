#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(SDL_Renderer *renderer, string filePath, float x, float y, int dirX, int dirY) {

	active = false;
	speed = 2.0;

	texture = IMG_LoadTexture(renderer, filePath.c_str());

	int w, h;
	//SDL_QueryTexture(texture , NULL,NULL,&w,&h);
	posRect.w = 64;
	posRect.h = 64;

	posRect.x = x - (posRect.w / 2);
	posRect.y = y;

	pos_X = x;
	pos_Y = y;

	//xDir = dirX;
	//yDir = dirY;

}

void PlayerBullet::Reset() {
	posRect.x = -1000;
	pos_X = posRect.x;
	active = false;

}

void PlayerBullet::Draw(SDL_Renderer *renderer) {
	SDL_RenderCopy(renderer, texture, NULL, &posRect);
}

void PlayerBullet::Update(float deltaTime) {

	if (active) {

		cout << posRect.x << "-" << posRect.y << "\n";
		pos_X += (speed) * deltaTime;
		posRect.x = (int)(pos_X + 0.5f);
		if ((posRect.y<(0 - posRect.h)) || (posRect.y>768) || (posRect.x<(0 - posRect.w)) || (posRect.x>1024)) {
			Reset();
		}
	}
}

