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
	
	bool is_jumping;
	int y_before_jump;
	float gravity;
	int min_jump_vel_y;
	int max_jump_vel_y;
	bool j_key_down;
	bool j_key_up; //stop adding height to the jump, ie stop starting the jump
};

#endif
