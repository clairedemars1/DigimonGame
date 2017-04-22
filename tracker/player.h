#ifndef GOOD_GUY_H
#define GOOD_GUY_H

#include <string>
#include "twowaymultisprite.h"

class Player : public TwoWayMultiSprite{
	
public:
	Player(): TwoWayMultiSprite("player"), 
		is_jumping(false), 
		gravity(Gamedata::getInstance().getXmlFloat("player/gravity"))
		{}
	Player(const Player& rhs): 
		TwoWayMultiSprite(rhs),
		is_jumping(false),
		gravity(Gamedata::getInstance().getXmlFloat("player/gravity"))	
		{}
	Player(const std::string& name): 
		TwoWayMultiSprite(name), 
		is_jumping(false),
		gravity(Gamedata::getInstance().getXmlFloat("player/gravity"))	
		{}
	void update(Uint32 ticks);

private:
	bool is_jumping;
	float gravity;
};

#endif
