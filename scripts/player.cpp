#include "player.h"

Player::Player(SDL_Renderer *renderer, string imagePath, string audioPath, float x, float y){
	posRect.x = x;
	posRect.y = y;
	posRect.w=100;
	posRect.h=100;

	speed = 900.0;

	pos_X = 0;

	string playerPath = imagePath + "player.png";

	texture = IMG_LoadTexture(renderer, playerPath.c_str());
}

void Player::Update(float deltaTime){


	if(posRect.x<100){
			posRect.x=100;

	}

	if(posRect.x>668 - posRect.w){
		posRect.x=668-posRect.w;

	}

}

void Player::Draw(SDL_Renderer *renderer){

	SDL_RenderCopy(renderer,texture, NULL,&posRect);

}

void Player::moveright(float timedelta){

	pos_X += speed * timedelta;
	posRect.x = (int)(pos_X + .5f);

}

void Player::moveleft(float timedelta){

	pos_X -= speed * timedelta;
	posRect.x = (int)(pos_X + .5f);

}
