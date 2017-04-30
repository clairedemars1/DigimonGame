#include <iostream>
#include "gamedata.h"
#include "twowayexplodingmultisprite.h"


//~ class Patroller: public TwoWayMultiSprite {
class Patroller: public TwoWayExplodingMultiSprite {
public:
	// disallow
	Patroller()=delete; // they need to specify the sprite
	Patroller(const Patroller&)=delete;

	Patroller(std::string xml_name, int x_pos);
	virtual void update_helper(Uint32 ticks);
	virtual void do_after_explosion();

private:
	int leftEndPoint;
	int patrolRange;
	
	void setXRandWithinRange(); // semi-randomly, really
	void setYRand(); // semi-randomly, really
	void advanceFrameRandomly();


};

