#include "twowayexplodingmultisprite.h"

TwoWayExplodingMultiSprite::TwoWayExplodingMultiSprite(const std::string& name): 
	TwoWayMultiSprite(name),
	explodingSprite(NULL),
	isExploding(false)
	{}
	
TwoWayExplodingMultiSprite::~TwoWayExplodingMultiSprite(){
	if (explodingSprite) delete explodingSprite;
}

//~ TwoWayExplodingMultiSprite::TwoWayExplodingMultiSprite(const TwoWayExplodingMultiSprite& rhs): 
	//~ regularSprite(), 
	//~ explodingSprite(rhs.explodingSprite),
	//~ isExploding(false)
	//~ {}
	
void TwoWayExplodingMultiSprite::explode(){
	if ( not isExploding ){
		Sprite temp(getName()+"_explosion");
		temp.setPosition( getPosition() );
		if (explodingSprite) delete explodingSprite;
		explodingSprite = new ExplodingSprite(temp);
		isExploding = true;
	} 
}

// change update and draw so they expode the sprite when appropriate
void TwoWayExplodingMultiSprite::update(Uint32 ticks){
	
	// does not call base class update
	setIsFacingRight();
	
	if (isExploding){
		explodingSprite->update( ticks );
		if (not explodingSprite->isExploding() ){ // explosion's done
			isExploding = false;
			do_after_explosion();
		}

	} else {
		update_helper(ticks);
	}
}

void TwoWayExplodingMultiSprite::draw() const {
	if (isExploding){
		explodingSprite->draw();
	} else {
		TwoWayMultiSprite::draw();
	}
}
