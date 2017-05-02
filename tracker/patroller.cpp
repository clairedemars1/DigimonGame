#include <iostream>
#include "patroller.h"

float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}

Patroller::Patroller(std::string xml_name, int x_pos, int player_width, int player_height):
	TwoWayExplodingMultiSprite(xml_name), 
	origPos(),
	leftEndPoint(x_pos),
	patrolRange(Gamedata::getInstance().getXmlInt(xml_name+"/patrolRange") ),
	currentMode(NORMAL),
	playerPos(),
	playerWidth(player_width),
	playerHeight(player_height),
	playerIsExploding(false),
	playerIsJumping(false)
	{
		leftEndPoint = x_pos; // set leftmost point of range
		// make out of sync
		setXRandWithinRange();
		setYRand();
		advanceFrameRandomly();
		origPos = getPosition();

	}
		
void Patroller::setXRandWithinRange(){
	setX(leftEndPoint + rand()%patrolRange); // so not in sync
}

void Patroller::do_after_explosion(){
	setXRandWithinRange();
}

void Patroller::goLeft()  { // todo: why this check?
  if (getX() > 0) setVelocityX( -abs(getVelocityX()) ); 
}
void Patroller::goRight() { setVelocityX( fabs(getVelocityX()) ); }
void Patroller::goUp()    { setVelocityY( -fabs(getVelocityY()) ); 
	 }
void Patroller::goDown()  { setVelocityY( fabs(getVelocityY()) ); }
	
void Patroller::update_helper_non_explosion(Uint32 ticks){
	advanceFrame(ticks);
	
	float x= getX()+getFrameWidth()/2;
	float y= getY()+getFrameHeight()/2;
	float player_x= playerPos[0]+playerWidth/2;
	float player_y= playerPos[1]+playerHeight/2;
	float distanceToEnemy = ::distance( x, y, player_x, player_y );

	if ( currentMode == NORMAL ){ // move in patrol range
		//~ std::cout << "normal mode" << std::endl;
		
		if(distanceToEnemy < sightDistance){	currentMode = CHASE;  }
			
		// only move horiz
		float incr = getVelocityX()  * static_cast<float>(ticks) * 0.001;
		setX(getX() + incr);
		
		if ( getX() < leftEndPoint) {
			setVelocityX( fabs( getVelocityX() ) );
		}
		if ( getX() > (leftEndPoint + patrolRange) ) {
			setVelocityX( -fabs( getVelocityX() ) );
		}  
	} else if (currentMode == CHASE){ // chase player
		//~ std::cout << "chase mode" << std::endl;
		
		if (not playerIsJumping){ //if jumping , still chase mode but physically stop
			if(distanceToEnemy > sightDistance  ||  playerIsExploding ){ 
				stopChase(); 
			} else {
				  if ( x < player_x ) goRight();
				  if ( x > player_x ) goLeft();
				  if ( y < player_y ) goDown();
				  if ( y > player_y ) goUp();
				  
				  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
				  setPosition(getPosition() + incr);	

			}
		}
	} else if (currentMode == GO_HOME ){
		int home_x = origPos[0] + getFrameWidth()/2;
		int home_y = origPos[1] + getFrameHeight()/2;
		
		if ( distance(x, y, home_x, home_y) < 50 ) { 
			currentMode = NORMAL; 
		} else {
			if (not playerIsJumping){
			  //~ bool close_in_x = false;
			  //~ bool close_in_y = false;
			  if ( x < home_x  ) goRight();
			  if ( x > home_x  ) goLeft();
			  if ( y < home_y  ) goDown();
			  if ( y > home_y  ) goUp();
			  
			  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
			  setPosition(getPosition() + incr);
			}
		}
	}
}

void Patroller::advanceFrameRandomly(){
		// move to a diff frame
	int r = rand()% 2;
	if (r == 0 ) {
		advanceFrame();
		advanceFrame();
	}
}

void Patroller::setYRand(){
	int yLimit = Gamedata::getInstance().getXmlInt("patroller/yLimit");
	int worldHeight = Gamedata::getInstance().getXmlInt("world/height");

	int upLim = yLimit - getFrameHeight();
	int lowLim = worldHeight - getFrameHeight();
	setY( upLim + rand()%(lowLim - upLim) ); 
	
}

void Patroller::stopChase(){
	// reset velocities  & position
	//~ setPosition(origPos);
	//~ setVelocity( Vector2f(Gamedata::getInstance().getXmlInt(getName()+"/speedX"), 
		//~ Gamedata::getInstance().getXmlInt(getName()+"/speedY")) );
	
	//~ currentMode = NORMAL;
	currentMode = GO_HOME;
}

