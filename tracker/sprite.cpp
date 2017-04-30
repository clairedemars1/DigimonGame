#include <cmath>
#include "sprite.h"
#include "gamedata.h"
#include "renderContext.h"

Sprite::Sprite(const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"), 
                    Gamedata::getInstance().getXmlInt(name+"/speedY")),
			100,
			100
           ),
  frame( RenderContext::getInstance()->getFrame(name) )
{ 
	frameWidth = frame->getWidth();
	frameHeight = frame->getHeight();
}

Sprite::Sprite(const Sprite& s) :
  Drawable(s), 
  frame(s.frame)
{ }

//~ const Sprite& Sprite::operator=(const Sprite& rhs){
Sprite& Sprite::operator=(const Sprite& rhs){
	
	Drawable::operator=(rhs);
	frame = rhs.frame;
	return *this;
	
}

void Sprite::draw() const { 
  frame->draw(getX(), getY()); 
}

void Sprite::update(Uint32 ticks) { 
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( std::abs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-frameHeight) {
    setVelocityY( -std::abs( getVelocityY() ) );
  }
  if ( getX() < 0) {
    setVelocityX( std::abs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-frameWidth) {
    setVelocityX( -std::abs( getVelocityX() ) );
  }  
  //don't change to keepInWorld(), since you want bounce capabilities
}
