#ifndef GOOD_GUY_H
#define GOOD_GUY_H

#include <string>
#include "twowaymultisprite.h"

class Player : public TwoWayMultiSprite{
	
public:
	Player();
	Player(const Player& rhs);
	Player(const std::string& name);
	void update(Uint32 ticks);
	void notify(std::string event);

private:
	int yLimit;
	
	bool isJumping;
	int yBeforeJump;
	float gravity;
	int minJumpVelY;
	int maxJumpVelY;
	bool jKeyDown;
	bool jKeyUp; //stop adding height to the jump, ie stop starting the jump
};

#endif
