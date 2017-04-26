#include <iostream>
#include "patroller.h"

void Patroller::update(Uint32 ticks){
	// stay in designated area, 1 patrol length right of starting loc
	advanceFrame(ticks);

	Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
	setPosition(getPosition() + incr);	
	
	
	// keep in patrolling range
	if ( getX() < origX) {
		setVelocityX( fabs( getVelocityX() ) );
	}
	if ( getX() > (origX + patrolRange) ) {
		setVelocityX( -fabs( getVelocityX() ) );
	}  
}


void Patroller::setX(float x){
	
	// or set x randomly
		// give them random x in the world, and random y on the ground
	//~ int worldWidth = Gamedata::getInstance().getXmlInt("world/width");
	//~ setX( rand()%(worldWidth - getFrameWidth() ) );

	TwoWayMultiSprite::setX(x);
	origX = getX();
}



void Patroller::advanceFrameRandomly(){
		// move to a diff frame
	int r = rand()% 3;
	if (r == 0 ) {
		advanceFrame();
	} else if (r == 1 ){
		advanceFrame();
		advanceFrame();
	} // else start on first frame
	
}

void Patroller::setYRand(){
	int yLimit = Gamedata::getInstance().getXmlInt("patroller/yLimit");
	int worldHeight = Gamedata::getInstance().getXmlInt("world/height");

	int upLim = yLimit - getFrameHeight();
	int lowLim = worldHeight - getFrameHeight();
	setY( upLim + rand()%(lowLim - upLim) ); 
	
}
