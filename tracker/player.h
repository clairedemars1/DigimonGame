#ifndef PLAYER_H
#define PLAYER_H

#include "twowayexplodingmultisprite.h"

class Player: public TwoWayExplodingMultiSprite {
public:
	Player(): TwoWayExplodingMultiSprite("player"){
		// set non exploding sprite
		setNonExplodingSprite();
	}
	
	//disallow
	Player(const Player&)=delete;
	Player& operator=(const Player&)=delete;
	
	virtual void setNonExplodingSprite();

};

#endif
