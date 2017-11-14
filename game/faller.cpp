#include "faller.h"
#include "multisprite.h"
#include "gamedata.h"

Faller::Faller(const std::string& name): MultiSprite(name){ 
		
	setX(rand()% Gamedata::getInstance().getXmlInt("world/width"));
	setY(-rand() % Gamedata::getInstance().getXmlInt("world/height"));
	int probability = rand()%20;
	if (probability == -1 ){ // make big 1/20 of the time
		setScaleFactor(1.0);
	} else { // make little 19/20 of the time
		setScaleFactor( ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) * (0.3)); // (0 to 0.5)
	}
}
	
void Faller::draw() const {
	frames[currentFrame]->draw(getX(), getY(), scaleFactor);
}

void Faller::update(Uint32 ticks) {
	advanceFrame(ticks);

	Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
	setPosition(getPosition() + incr);

	//~ if ( getY() < frameHeight) {
	//~ setVelocityY( fabs( getVelocityY() ) );
	//~ }
	if ( getY() > worldHeight+frameHeight) { // has fallen all the way down, so respawn at top
	setY(-frameHeight);
	setX(rand()%worldWidth);
	}

	if ( getX() < 0) {
	setVelocityX( fabs( getVelocityX() ) );
	}
	if ( getX() > worldWidth-frameWidth) {
	setVelocityX( -fabs( getVelocityX() ) );
	}  
}
