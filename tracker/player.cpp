#include <iostream>
#include <array>
#include <cmath>
#include <SDL.h>
#include "engine.h"
#include "player.h"

Player::Player(): TwoWayMultiSprite("player"), 
	yLimit(Gamedata::getInstance().getXmlInt("player/yLimit")),
	is_jumping(false), 
	y_before_jump(0),
	gravity(Gamedata::getInstance().getXmlFloat("player/gravity")),
	min_jump_vel_y(Gamedata::getInstance().getXmlInt("player/minJumpSpeedY")),
	max_jump_vel_y(Gamedata::getInstance().getXmlInt("player/maxJumpSpeedY")),
	j_key_down(false),
	j_key_up(false)
	{}
Player::Player(const Player& rhs): 
	TwoWayMultiSprite(rhs),
	yLimit(Gamedata::getInstance().getXmlInt("player/yLimit")),
	is_jumping(false),
	y_before_jump(0),
	gravity(Gamedata::getInstance().getXmlFloat("player/gravity")),
	min_jump_vel_y(Gamedata::getInstance().getXmlInt("player/minJumpSpeedY")),
	max_jump_vel_y(Gamedata::getInstance().getXmlInt("player/maxJumpSpeedY")),
	j_key_down(false),
	j_key_up(false)
	{}
Player::Player(const std::string& name): 
	TwoWayMultiSprite(name), 
	yLimit(Gamedata::getInstance().getXmlInt("player/yLimit")),	
	is_jumping(false),
	y_before_jump(0),
	gravity(Gamedata::getInstance().getXmlFloat("player/gravity")),
	min_jump_vel_y(Gamedata::getInstance().getXmlInt("player/minJumpSpeedY")),
	max_jump_vel_y(Gamedata::getInstance().getXmlInt("player/maxJumpSpeedY")),
	j_key_down(false),
	j_key_up(false)
	{}

void Player::notify(std::string event){
	// event options: j_key_down, j_key_up
	if (event == "j_key_down") j_key_down = true;
	if (event == "j_key_up") j_key_up = true;
	
}


//~ void Player::update(Uint32 ticks, const std::array<char, 2> &directions){
void Player::update(Uint32 ticks){
	std::array<char, 2> directions;
	const Uint8* keystate; 
	
	advanceFrame(ticks);
	
	
	// step 1: get instructions
	// jumping
	if (j_key_down){
		y_before_jump = getY();
		j_key_down = false;
		is_jumping = true;
		
		setVelocityY(min_jump_vel_y);
	}
	if (j_key_up) {
		
		if ( getVelocityY() > min_jump_vel_y) { setVelocityY(max_jump_vel_y); }
		j_key_up = false;
	}
	
	// asdw keys
	keystate = SDL_GetKeyboardState(NULL); 
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
	if (is_jumping){
		
		// move x based on x vel
		moveHoriz(ticks); 

		// apply gravity
		setVelocityY(getVelocityY()*static_cast<float>(ticks)*0.001);
		moveVert(ticks);
		
		// if we get below y where started jump, then actually end jump
		if (getY() >= y_before_jump){
			is_jumping = false;
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
}

