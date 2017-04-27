#ifndef PLAYER_NON_EXPLODING_H
#define PLAYER_NON_EXPLODING_H

#include <string>
#include "twowaymultisprite.h"

class PlayerNonExploding : public TwoWayMultiSprite{
	
public:
	PlayerNonExploding();
	PlayerNonExploding(const PlayerNonExploding& rhs);
	PlayerNonExploding(const std::string& name);
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
