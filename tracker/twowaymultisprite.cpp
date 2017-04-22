#include "twowaymultisprite.h"

TwoWayMultiSprite::TwoWayMultiSprite(const std::string& name): MultiSprite(name){}

TwoWayMultiSprite::TwoWayMultiSprite(const TwoWayMultiSprite& rhs): MultiSprite(rhs){}

void TwoWayMultiSprite::draw() const{

  bool flip = false;
  if ( getVelocityX() < 0 ) flip = true;
  frames[currentFrame]->draw(getX(), getY(), flip);
}
