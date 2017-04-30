#ifndef PLAYER_H
#define PLAYER_H

#include "twowayexplodingmultisprite.h"
#include "bulletPool.h"

class Player: public TwoWayExplodingMultiSprite {
public:
	Player();
	virtual void draw() const ;
	virtual void update_helper(Uint32 ticks); // define the pure virtual function used in base class's update
	void notify(std::string event); // rename to "hear"
	virtual void do_after_explosion();// define pure virtual
	void shoot();
	bool isBulletHitting(const Drawable* obj) const;
	
	//disallow some
	Player(const Player& rhs)=delete;
	Player& operator=(const Player&)=delete;

private:
	int yLimit;
	
	bool isJumping;
	int yBeforeJump;
	float gravity;
	int minJumpVelY;
	int maxJumpVelY;
	bool jKeyDown;
	bool jKeyUp; //stop adding height to the jump, ie stop starting the jump
	
	std::string bulletName;
	BulletPool bullets;
	int minSpeed;
	

};
#endif
