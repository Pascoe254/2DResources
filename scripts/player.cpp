#include "player.h"

Player::Player(SDL_Renderer *renderer, string imagePath, string audioPath, float x, float y){
	posRect.x = x;
	posRect.y = normaly = y;
	posRect.w=90;
	posRect.h=150;

	backH.x =  10;
	backH.y =  20;
	backH.w =  40;
	backH.h =  160;

	frontH.x = 15;
	frontH.y = 24;
	frontH.w = 31;
	frontH.h = 152;

	backa.x = 60;
	backa.y = 20;
	backa.w = 40;
	backa.h = 160;

	fronta.x = 65;
	fronta.y = 24;
	fronta.w = 31;
	fronta.h = 152;


	puback.x = 900;
	puback.y = 24;
	puback.w = 100;
	puback.h = 100;

	climb = false;

	//pu1.x = pu2.x = pu3.x = 900;
	//pu1.y = pu2.y = pu3.y = 24;
	//pu1.w = pu2.w = pu3.w = 100;
	//pu1.h = pu2.h = pu3.h = 100;
	firetime = hittime = 0;

	speed = 4.0;

	pos_X = 0;
	pos_Y = 0;

	shoot = true;

	playerjump = false;

	jumpcount = 0;

	jumppos = 0;


	string playerPath = imagePath + "player1.png";
	texture = IMG_LoadTexture(renderer, playerPath.c_str());


	playerPath = imagePath + "uiback.png";
	backhealth = IMG_LoadTexture(renderer, playerPath.c_str());

	playerPath = imagePath + "uifront.png";
	fronthealth = IMG_LoadTexture(renderer, playerPath.c_str());

	playerPath = imagePath + "ammoback.png";
	backammo = IMG_LoadTexture(renderer, playerPath.c_str());

	playerPath = imagePath + "ammofront.png";
	frontammo = IMG_LoadTexture(renderer, playerPath.c_str());

	playerPath = imagePath + "pickupback.png";
	frontorbs = IMG_LoadTexture(renderer, playerPath.c_str());

	playerPath = imagePath + "pickup1.png";
	backorbs1 = IMG_LoadTexture(renderer, playerPath.c_str());

	playerPath = imagePath + "pickup2.png";
	backorbs2 = IMG_LoadTexture(renderer, playerPath.c_str());

	playerPath = imagePath + "pickup3.png";
	backorbs3 = IMG_LoadTexture(renderer, playerPath.c_str());

	string bulletPath = imagePath + "turretbullet.png";

	for (int i = 0; i<10; i++) {

		PlayerBullet tmpBullet(renderer, bulletPath, -1000, -1000, 0, 0);

		bulletList.push_back(tmpBullet);
	}
}

void Player::Update(float deltatime){

	if(movepleft){
		moveleft(deltatime);
	}

	if(movepright){
		moveright(deltatime);
	}

	if(posRect.x<100){
			posRect.x=100;
			pos_X = posRect.x;
			movebleft = true;

	}

	if(posRect.x>800 - posRect.w){
		posRect.x=800-posRect.w;
		pos_X = posRect.x;
		movebright = true;
	}

	for (int i = 0; i<bulletList.size(); i++) {
		if (bulletList[i].active) {
			bulletList[i].Update(deltatime);
		}
	}

	

}

void Player::ammo() {
	if (SDL_GetTicks() > firetime) {
		firetime = SDL_GetTicks() + 1000;
		shoot = true;
		
	}
	if (shoot && ammoused < 100) {
		ammoused += 5;
		fronta.y += ammoused;
		fronta.h -= ammoused;
		shoot = false;
	}


	if (ammoused > 100) {
		ammoused = 100;
	}
}

void Player::health() {
	if (SDL_GetTicks() > firetime) {
		firetime = SDL_GetTicks() + 1000;
		hit = true;
	}
	if (hit && damage < 100) {
		damage += 5;
		frontH.y += damage;
		frontH.h -= damage;
		hit = false;
	}


	if (damage > 100) {
		damage = 100;
	}
}

void Player::turrethit() {

	
	if (damage < 100) {
		damage += 5;
		frontH.y += damage;
		frontH.h -= damage;
		
	}


	if (damage > 100) {
		damage = 100;
	}
}

void Player::Draw(SDL_Renderer *renderer){

	SDL_RenderCopy(renderer,texture, NULL,&posRect);
	SDL_RenderCopy(renderer, backhealth, NULL, &backH);
	SDL_RenderCopy(renderer, fronthealth, NULL, &frontH);
	SDL_RenderCopy(renderer, backammo, NULL, &backa);
	SDL_RenderCopy(renderer, frontammo, NULL, &fronta);
	SDL_RenderCopy(renderer, frontorbs, NULL, &puback);
	if (orb1) {
		SDL_RenderCopy(renderer, backorbs1, NULL, &puback);
	}
	if (orb2) {
		SDL_RenderCopy(renderer, backorbs2, NULL, &puback);
	}
	if (orb3) {
		SDL_RenderCopy(renderer, backorbs3, NULL, &puback);
	}
	for (int i = 0; i<bulletList.size(); i++) {
		if (bulletList[i].active) {
			bulletList[i].Draw(renderer);
		}
	}
}

void Player::moveright(float timedelta){

	pos_X += speed * timedelta;
	posRect.x = (int)(pos_X + .5f);

}

void Player::moveleft(float timedelta){

	pos_X -= speed * timedelta;
	posRect.x = (int)(pos_X + .5f);

}

void Player::jump(){



		jumppos = .02*(jumpcount * jumpcount) - 200;
		pos_Y = normaly + jumppos;
		posRect.y = (int)(pos_Y + 0.5f);
		jumpcount+=1;

		if (jumpcount > 100) {
			playerjump = false;
			jumpcount = 0;
		}
}

void Player::release(SDL_Event event){
	switch(event.key.keysym.sym){
	case SDLK_a:
		movepleft = false;
		break;
	case SDLK_d:
		movepright=false;
		break;
	case SDLK_w:
			climb=false;
			break;
	}

}

void Player::press(SDL_Event event){
	switch(event.key.keysym.sym){
		case SDLK_a:
			movepleft = true;
			break;
		case SDLK_d:
			movepright = true;
			break;
		case SDLK_w:
				climb = true;
			break;
		case SDLK_SPACE:
			CreateBullet();
			ammo();
			break;
		}
}

void Player::CreateBullet() {

	for (int i = 0; i < bulletList.size(); i++) {

		if (bulletList[i].active == false) {


			bulletList[i].active = true;

			bulletList[i].posRect.x = (posRect.x + (posRect.w / 2));
			bulletList[i].posRect.y = (posRect.y + (posRect.h / 2));

			bulletList[i].posRect.x = bulletList[i].posRect.x - (bulletList[i].posRect.w / 2);
			bulletList[i].posRect.y = bulletList[i].posRect.y - (bulletList[i].posRect.h / 2);

			bulletList[i].pos_X = bulletList[i].posRect.x;
			bulletList[i].pos_Y = bulletList[i].posRect.y;

			break;
		}
	}
}
