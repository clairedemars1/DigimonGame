#include <iostream>
#include <array>
#include <cmath>
#include "engine.h"
#include "player.h"

void Player::update(Uint32 ticks, const std::array<char, 2> &directions){
	
	advanceFrame(ticks);
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

