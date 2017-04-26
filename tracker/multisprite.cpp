#include "multisprite.h"
#include "gamedata.h"
#include "renderContext.h"

void MultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}
void MultiSprite::advanceFrame() {
    currentFrame = (currentFrame+1) % numberOfFrames;
}

MultiSprite::MultiSprite( const std::string& name) :
    Drawable(name,
		Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
				Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
		Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"), 
				Gamedata::getInstance().getXmlInt(name+"/speedY")),
		100,
		100
	),
  frames( RenderContext::getInstance()->getFrames(name) ),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 )
{ 
	frameWidth = frames[0]->getWidth(); // had to be here b/c need frameWidth to be in drawable, to prevent duplicate code for keepInWorld()
	frameHeight = frames[0]->getHeight();
}

MultiSprite::MultiSprite( const std::string& name, int startX, int startY) :
    Drawable(name,
		Vector2f(startX, startY), 
		Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"), 
				Gamedata::getInstance().getXmlInt(name+"/speedY")),
		100,
		100
	),
  frames( RenderContext::getInstance()->getFrames(name) ),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 )
{ 
	frameWidth = frames[0]->getWidth(); // had to be here b/c need frameWidth to be in drawable, to prevent duplicate code for keepInWorld()
	frameHeight = frames[0]->getHeight();
}



MultiSprite::MultiSprite(const MultiSprite& s) :
  Drawable(s), 
  frames(s.frames),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame )
  //~ worldWidth( s.worldWidth ),
  //~ worldHeight( s.worldHeight ),
  //~ frameWidth( s.frameWidth ),
  //~ frameHeight( s.frameHeight )
  { }

void MultiSprite::draw() const { 

  frames[currentFrame]->draw(getX(), getY());
}

void MultiSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-frameHeight) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-frameWidth) {
    setVelocityX( -fabs( getVelocityX() ) );
  }  

}

  void MultiSprite::setFrames(const std::string& name){
	  frames = RenderContext::getInstance()->getFrames(name);
	  currentFrame = 0;
	  numberOfFrames =  Gamedata::getInstance().getXmlInt(name+"/frames");
	  frameInterval = Gamedata::getInstance().getXmlInt(name+"/frameInterval");
	  timeSinceLastFrame = 0 ;
	  frameWidth = frames[0]->getWidth();
	  frameHeight = frames[0]->getHeight();
  }

void MultiSprite::moveHoriz(Uint32 ticks){
	float incr = getVelocityX() * static_cast<float>(ticks) * 0.001;
	setX(getX() + incr);
}

void MultiSprite::moveVert(Uint32 ticks){
	float incr = getVelocityY() * static_cast<float>(ticks) * 0.001;
	setY(getY() + incr);
}
