#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include "twowayexplodingmultisprite.h"
#include "bulletPool.h"
#include "patroller.h"


class Player: public TwoWayExplodingMultiSprite {
public:
	Player();
	~Player(); 
	virtual void draw() const ;
	virtual void update_helper_non_explosion(Uint32 ticks); // define the pure virtual function used in base class's update
	virtual void update_helper_always(); 
	void receive_command(std::string event);
	virtual void do_after_explosion();// define pure virtual
	void shoot();
	bool isBulletHitting(const Drawable* obj) const;
	void attach(Patroller* p){ observers.push_back(p); }
	void detach(const Patroller* find_me);
	
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
	std::list<Patroller*> observers;

	void notifyObservers();
	

};
#endif
