#include <iostream>
#include <array>
#include <cmath>
#include <SDL.h>
#include "engine.h"
#include "player.h"

//~ void Player::update(Uint32 ticks, const std::array<char, 2> &directions){
void Player::update(Uint32 ticks){
	std::array<char, 2> directions;
	const Uint8* keystate; 
	advanceFrame(ticks);
	
	// jumping
	
	
	
	// asdw keys
	keystate = SDL_GetKeyboardState(NULL); // define here in case while doesn't run
	directions = {0, 0}; // horiz, vert. Each can be -1 0 or 1
	if ( keystate[SDL_SCANCODE_A] ) {
	  directions[0]--; // left
	}
	if ( keystate[SDL_SCANCODE_D]) {
	  directions[0]++; // right
	}
	if ( keystate[SDL_SCANCODE_S] ) {
	  directions[1]--; // down 
	}
	if ( keystate[SDL_SCANCODE_W] ) {
	  directions[1]++; // up
	}
	
	
	
	
	 if (directions[0]){ // can be -1, 0, 1 & indicates horiz movement
		 setVelocityX(directions[0]*fabs(getVelocityX()));
		 moveHoriz(ticks); 
	 }
	 if (directions[1]){ // vertical movement from keys
		 
		 if (getY() > 230 || directions[1] < 0){ // only allow if player is not too high or player is moving down
			 setVelocityY(directions[1]*-fabs(getVelocityY()) ); // add a negative b/c y increases as you go down
			 moveVert(ticks);
		 }
	 }
	 
	 

	 keepInWorld();
}

