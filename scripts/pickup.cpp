#include "pickup.h"
Pickup::Pickup(SDL_Renderer * renderer, int iden, string imagepath, string audiopath, float x, float y) {


	identifier = iden;
	if (identifier == 1) {
		string imagePath = imagepath + "orb.png";
		Tex = IMG_LoadTexture(renderer, imagePath.c_str());
	}

	pickupRect.x = x;
	pickupRect.y = y;
	pickupRect.h = 64;
	pickupRect.w = 64;

	active = true;

}


void Pickup::draw(SDL_Renderer * renderer) {
	if(active){
		SDL_RenderCopy(renderer, Tex, NULL, &pickupRect);
	}
}