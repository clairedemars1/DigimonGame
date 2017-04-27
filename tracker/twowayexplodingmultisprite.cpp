#include "twowayexplodingmultisprite.h"

TwoWayExplodingMultiSprite::TwoWayExplodingMultiSprite(const std::string& name): 
	nonExplodingSprite(NULL), 
	explodingSprite(new Sprite(name+"/explosionFile")),
	isExploding(false)
	{
		//~ std::cout << "\ndon't forget to call setNonExplodingSprite()!!!!!!!" << std::endl;
	}

//~ TwoWayExplodingMultiSprite::TwoWayExplodingMultiSprite(const TwoWayExplodingMultiSprite& rhs): 
	//~ regularSprite(), 
	//~ explodingSprite(rhs.explodingSprite),
	//~ isExploding(false)
	//~ {}


TwoWayExplodingMultiSprite::~TwoWayExplodingMultiSprite(){
	delete nonExplodingSprite;
	delete explodingSprite;
}


// change update and draw so they expode the sprite when appropriate
void TwoWayExplodingMultiSprite::update(Uint32 ticks){
	
	if (isExploding and not (dynamic_cast<ExplodingSprite*>(explodingSprite))->isExploding()) { isExploding = false; }

	if (isExploding){
		// update the exploding sprite
		explodingSprite->update( ticks);
	} else {
		// update the regular sprite
		nonExplodingSprite->update(ticks);
		//~ TwoWayMultiSprite::update(Uint32 ticks);
		//todo: update regular sprite
	}
	
}

void TwoWayExplodingMultiSprite::draw(){
	if (isExploding){
		explodingSprite->draw();
	} else {
		nonExplodingSprite->draw();
	}
}
