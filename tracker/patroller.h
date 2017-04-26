#include <iostream>
#include "gamedata.h"
#include "twowaymultisprite.h"


class Patroller: public TwoWayMultiSprite {
public:
	Patroller()=delete; // they need to specify the sprite
	Patroller(std::string xml_name, int x_pos): 
		TwoWayMultiSprite(xml_name), 
		origX(x_pos),
		patrolRange(Gamedata::getInstance().getXmlInt(xml_name+"/patrolRange") ){
			setX(x_pos);
			origX = x_pos;
			setYRand();
			advanceFrameRandomly();
			
		}
	Patroller(const Patroller& rhs):
		TwoWayMultiSprite(rhs),
		origX(rhs.origX),
		patrolRange(rhs.patrolRange){}
	virtual void update(Uint32 ticks);
	virtual void setX(float x);


private:
	int origX;
	int patrolRange;
	
	void advanceFrameRandomly();
	void setYRand();
};

