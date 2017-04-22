#ifndef GOOD_GUY_H
#define GOOD_GUY_H

#include <string>
#include "twowaymultisprite.h"

class Player : public TwoWayMultiSprite{
	
public:
	Player(const std::string& name): TwoWayMultiSprite(name) {}
	Player(const Player& rhs): TwoWayMultiSprite(rhs){}
	void update(Uint32 ticks, const std::array<char, 2> &directions);

};

#endif
