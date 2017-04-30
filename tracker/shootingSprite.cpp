#include "shootingSprite.h"
#include "gamedata.h"

ShootingSprite::ShootingSprite(const std::string& name) :
  Sprite(name),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
  bullets( bulletName ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") )
{ }

ShootingSprite::ShootingSprite(const ShootingSprite& s) :
  Sprite(s),
  bulletName(s.bulletName),
  bullets(s.bullets),
  minSpeed(s.minSpeed)
{ }

void ShootingSprite::shoot() { 
  float y = getY()+getFrame()->getHeight()/2;
  float x;
  int x_speed = getVelocityX();;
  if ( getVelocityX() > 0 ){ // insufficient
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

bool ShootingSprite::collidedWith(const Drawable* obj) const {
  return bullets.collidedWith( obj );
}

void ShootingSprite::draw() const { 
  Sprite::draw();
  bullets.draw();
}

void ShootingSprite::update(Uint32 ticks) { 
  Sprite::update(ticks);
  bullets.update(ticks);
}

