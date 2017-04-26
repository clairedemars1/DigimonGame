#include <iostream>
#include "gamedata.h"
#include "twowaymultisprite.h"


class Patroller: public TwoWayMultiSprite {
public:
	Patroller()=delete; // they need to specify the sprite
	Patroller(std::string xml_name, int x_pos): 
		TwoWayMultiSprite(xml_name), 
		leftEndPoint(x_pos),
		patrolRange(Gamedata::getInstance().getXmlInt(xml_name+"/patrolRange") ){
			leftEndPoint = x_pos; // set leftmost point of range
			
			setX(x_pos + rand()%patrolRange); // so not in sync
			//~ std::cout << origX << " " <<getX() << std::endl;

			setYRand();
			advanceFrameRandomly(); // so really not in sync
			
		}
	Patroller(const Patroller& rhs):
		TwoWayMultiSprite(rhs),
		leftEndPoint(rhs.leftEndPoint),
		patrolRange(rhs.patrolRange){}
	virtual void update(Uint32 ticks);


private:
	int leftEndPoint;
	int patrolRange;
	
	void advanceFrameRandomly();
	void setYRand();
};

