#ifndef PATROLLER_H
#define PATROLLER_H

#include <iostream>
#include "gamedata.h"
#include "twowayexplodingmultisprite.h"


//~ class Patroller: public TwoWayMultiSprite {
class Patroller: public TwoWayExplodingMultiSprite {
public:
	// disallow
	Patroller()=delete; // they need to specify the sprite
	Patroller(const Patroller&)=delete;

	Patroller(std::string xml_name, int x_pos, int player_width, int player_height);
	virtual void update_helper_non_explosion(Uint32 ticks);
	virtual void do_after_explosion();
	void notify(const Vector2f& p, bool player_is_exploding){ 
		playerPos = p;
		playerIsExploding = player_is_exploding;
	}

private:
	enum MODE {NORMAL, CHASE};
	Vector2f origPos;
	int leftEndPoint;
	int patrolRange;
	MODE currentMode;
	Vector2f playerPos;
	int playerWidth;
	int playerHeight;
	bool playerIsExploding;
	static float sightDistance; // so all patrollers share the same distance
	
	void setXRandWithinRange(); // semi-randomly, really
	void setYRand(); // semi-randomly, really
	void advanceFrameRandomly();
	void goLeft();
	void goRight();
	void goUp();  
	void goDown(); 
	void stopChase();


};

#endif
