#include "twowayexplodingmultisprite.h"

TwoWayExplodingMultiSprite::TwoWayExplodingMultiSprite(const std::string& name): 
	TwoWayMultiSprite(name),
	explodingSprite( Sprite(name+"_explosion") ),
	isExploding(false)
	{}

//~ TwoWayExplodingMultiSprite::TwoWayExplodingMultiSprite(const TwoWayExplodingMultiSprite& rhs): 
	//~ regularSprite(), 
	//~ explodingSprite(rhs.explodingSprite),
	//~ isExploding(false)
	//~ {}

// change update and draw so they expode the sprite when appropriate
void TwoWayExplodingMultiSprite::update(Uint32 ticks){
	
	if (isExploding){
		if ( not explodingSprite.isExploding() ){ // only change position the first time
			explodingSprite.setPosition( getPosition() );
		}
		
		explodingSprite.update( ticks ); // if expl sprite is done, he'll say so
		
		// idea: if it thinks it's exploding but the guy doing the exploding is actually done, tell it it's not actually exploding
		// note: put here else would set isExploding = false as soon as you set it to true
		if (not (explodingSprite.isExploding()) ) { 
			isExploding = false; 
			do_after_explosion();
		}
	} else {
		update_helper(ticks);
	}
	
	
		

}

void TwoWayExplodingMultiSprite::draw() const {
	if (isExploding){
		explodingSprite.draw();
	} else {
		TwoWayMultiSprite::draw();
	}
}
