#ifndef TWO_WAY_EXPLODING_MULTISPRITE_H
#define TWO_WAY_EXPLODING_MULTISPRITE_H

#include "twowaymultisprite.h"
#include "explodingSprite.h"

// abstract base class
class TwoWayExplodingMultiSprite: public TwoWayMultiSprite{
public:
	//disallow
	TwoWayExplodingMultiSprite(const TwoWayExplodingMultiSprite&)=delete;
	TwoWayExplodingMultiSprite& operator=(const TwoWayExplodingMultiSprite&)=delete;

	TwoWayExplodingMultiSprite(const std::string&); 
	void explode() { isExploding = true; } // update() unsets it later
	virtual void update(Uint32 ticks);
	virtual void draw() const;
	
	
	bool getIsExploding() { return isExploding; }
	
	//make the class abstract	
	virtual void update_helper(Uint32 ticks)=0; // add to the update function
	virtual void do_after_explosion()=0;

	
protected:
	ExplodingSprite explodingSprite;

private:
	bool isExploding;
	
};
 
#endif
