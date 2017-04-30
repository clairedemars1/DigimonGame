#include "twowaymultisprite.h"

TwoWayMultiSprite::TwoWayMultiSprite(const std::string& name): MultiSprite(name), isFacingRight(true){}

TwoWayMultiSprite::TwoWayMultiSprite(const TwoWayMultiSprite& rhs): MultiSprite(rhs), isFacingRight(true){}

void TwoWayMultiSprite::update(Uint32 ticks) {
	MultiSprite::update(ticks);
	

	setIsFacingRight();
}

void TwoWayMultiSprite::setIsFacingRight(){
	// we dont change isFacingRight if velocity is 0, so that after moving in a given direction, the guy stays facing in that direction
	if (getVelocityX() < 0){
	  isFacingRight = false;
	} else if (getVelocityX() > 0){
	  isFacingRight = true;
	}
}

void TwoWayMultiSprite::draw() const {

  bool flip = false;
  if ( getVelocityX() < 0 ){ 
	  flip = true;
  } else if (getVelocityX() > 0 ){
  }
  frames[currentFrame]->draw(getX(), getY(), flip);
}
