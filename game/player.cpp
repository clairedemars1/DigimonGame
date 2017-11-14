#include <iostream>
#include <array>
#include <cmath>
#include <SDL.h>
#include "engine.h"
#include "player.h"

Player::Player(): TwoWayExplodingMultiSprite("player"),
	yLimit(Gamedata::getInstance().getXmlInt("player/yLimit")),
	isJumping(false),
	yBeforeJump(0),
	gravity(Gamedata::getInstance().getXmlFloat("player/gravity")),
	minJumpVelY(Gamedata::getInstance().getXmlInt("player/minJumpSpeedY")),
	maxJumpVelY(Gamedata::getInstance().getXmlInt("player/maxJumpSpeedY")),
	jKeyDown(false),
	jKeyUp(false),
	bulletName( Gamedata::getInstance().getXmlStr("player/bullet") ),
	bullets( bulletName ),
	minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ),
	observers(),
	xToWin( Gamedata::getInstance().getXmlInt("world/width") - getFrameWidth() - 40 ),
	hasWon(false)
	{}

Player::~Player(){
	// engine deletes observers
}

void Player::draw() const {
	TwoWayExplodingMultiSprite::draw();
	bullets.draw();
	
}

void Player::receive_command(std::string event){
	// event options: jKeyDown, jKeyUp
	if (event == "jKeyDown") jKeyDown = true; 
	if (event == "jKeyUp") jKeyUp = true; //todo unset jKeyDown?
}


void Player::shoot(){
  float y = getY()+(0.25)*getFrame()->getHeight();
  float x;
  int x_speed = getVelocityX();;
  if ( mIsFacingRight() ){ // insufficient
	x = getX()+getFrame()->getWidth();
	x_speed += minSpeed;

  } else {
	x = getX()-getFrame()->getWidth();
	x_speed -= minSpeed;
  }
 
  // I'm not adding minSpeed to y velocity:
  bullets.shoot( Vector2f(x, y), 
    Vector2f(x_speed, 0)
  );
}

bool Player::isBulletHitting(const Drawable* obj) const {
	return bullets.collidedWith(obj);
}

//~ void Player::update(Uint32 ticks, const std::array<char, 2> &directions){
void Player::update_helper_non_explosion(Uint32 ticks){
	
	std::array<char, 2> directions;
	const Uint8* keystate; 

	advanceFrame(ticks);
		
	// step 1: get instructions
	if (jKeyDown){ // jumping
		// note that 2 forces limit the velocity: gravity and releasing the jump key
		// 		thus if you release late, you ahve a large velocity for a long time, and get high
		//		ie let it run at high velocity until release jump key, then both drop it and allow gravity to decrease it
		// only allow if he's on the ground
		if (not isJumping) {
			yBeforeJump = getY();
			jKeyDown = false;
			isJumping = true; 
			//~ std::cout << "setting isJumping" <<std::endl;
			
			bool vel_is_neg = (getVelocityX() < 0);
			int multiply_by = 1;
			if (vel_is_neg) multiply_by = -1;
			setVelocityX(multiply_by * Gamedata::getInstance().getXmlInt("player/jumpSpeedX"));
			setVelocityY(maxJumpVelY);
		}
	}
	if (jKeyUp) {
		if ( getVelocityY() > minJumpVelY) { setVelocityY(minJumpVelY); }
		jKeyUp = false;
	}
	
	keystate = SDL_GetKeyboardState(NULL); // asdw keys
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

	
	// step 2: move based on instructions
	if (isJumping){

		// move x based on x vel that was set when jump started
		moveHoriz(ticks); 

		// apply gravity
		setVelocityY(getVelocityY() + gravity*static_cast<float>(ticks)*0.001);
		moveVert(ticks);
		
		// if we get below y where started jump, then actually end jump
		if (getY() > yBeforeJump){
			bool vel_is_neg = (getVelocityX() < 0);
			int multiply_by = 1;
			if (vel_is_neg) multiply_by = -1;
			
			setVelocity( Vector2f(multiply_by * Gamedata::getInstance().getXmlInt(getName()+"/speedX"), 
					Gamedata::getInstance().getXmlInt(getName()+"/speedY")) );
			isJumping = false;
		}
	} else { // allow adws keys
	
		 if (directions[0]){ // can be -1, 0, 1 & indicates horiz movement
			 setVelocityX(directions[0]*fabs(getVelocityX()));
			 moveHoriz(ticks); 
		 }
		 if (directions[1]){ // vertical movement from keys
			 
			 if (getY() > yLimit || directions[1] < 0){ // only allow if player is not too high or player is moving down
				 setVelocityY(directions[1]*-fabs(getVelocityY()) ); // add a negative b/c y increases as you go down
				 moveVert(ticks);
			 }
		 }
	 }
	 keepInWorld();
	 
	// bullets
	if (keystate[SDL_SCANCODE_SPACE] ){
		shoot();
	}
	bullets.update(ticks);
}
void Player::update_helper_always(){
	notifyObservers();
	//~ std::cout << getX() << " "<< xToWin <<std::endl;
	if (getX() > xToWin ){
		hasWon = true;
	}
}

void Player::do_after_explosion(){
	// respawn at original position
	setX(Gamedata::getInstance().getXmlInt("player/startLoc/x"));
	setY(Gamedata::getInstance().getXmlInt("player/startLoc/y"));
}

void Player::notifyObservers(){
	for (auto o: observers){
		o->notify(getPosition(), getIsExploding(), isJumping);
	}
}

void Player::detach(const Patroller* find_me){
	auto it = observers.begin();
	while (it != observers.end()){
		if( *it == find_me ){
			it =observers.erase(it);
			return;
		}
		it++;
	}
}

void Player::reset(){
	setVelocity(Vector2f(Gamedata::getInstance().getXmlInt(getName()+"/speedX"), 
					Gamedata::getInstance().getXmlInt(getName()+"/speedY"))	
					);
	setPosition(Vector2f(Gamedata::getInstance().getXmlInt(getName()+"/startLoc/x"), 
					Gamedata::getInstance().getXmlInt(getName()+"/startLoc/y"))
					);
	hasWon = false;
}
