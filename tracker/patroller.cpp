#include <iostream>
#include "patroller.h"

void Patroller::update(Uint32 ticks){
	// stay in designated area, 1 patrol length right of starting loc
	advanceFrame(ticks);

	Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
	setPosition(getPosition() + incr);	
	
	
	// keep in patrolling range
	if ( getX() < leftEndPoint) {
		setVelocityX( fabs( getVelocityX() ) );
	}
	if ( getX() > (leftEndPoint + patrolRange) ) {
		setVelocityX( -fabs( getVelocityX() ) );
	}  
}


void Patroller::advanceFrameRandomly(){
		// move to a diff frame
	int r = rand()% 2;
	if (r == 0 ) {
		std::cout << "case 1" << std::endl;
		//~ advanceFrame();
	} else if (r == 1 ){
		std::cout << "case 2" << std::endl;

		advanceFrame();
		advanceFrame();
	} // else start on first frame
	else	std::cout << "case 3" << std::endl;
}

void Patroller::setYRand(){
	int yLimit = Gamedata::getInstance().getXmlInt("patroller/yLimit");
	int worldHeight = Gamedata::getInstance().getXmlInt("world/height");

	int upLim = yLimit - getFrameHeight();
	int lowLim = worldHeight - getFrameHeight();
	setY( upLim + rand()%(lowLim - upLim) ); 
	
}
