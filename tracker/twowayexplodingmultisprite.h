#ifndef TWO_WAY_EXPLODING_MULTISPRITE_H
#define TWO_WAY_EXPLODING_MULTISPRITE_H

#include "twowaymultisprite.h"
#include "explodingSprite.h"

// Meyers: prefer composition to inheritance
// abstract base class
class TwoWayExplodingMultiSprite {
public:
	//disallow
	TwoWayExplodingMultiSprite(const TwoWayExplodingMultiSprite&)=delete;
	TwoWayExplodingMultiSprite& operator=(const TwoWayExplodingMultiSprite&)=delete;

	TwoWayExplodingMultiSprite(const std::string&); 
	~TwoWayExplodingMultiSprite(); 
	void explode() { isExploding = true; } // update() unsets it later
	virtual void update(Uint32 ticks);
	virtual void draw();
	
	
	bool getIsExploding() { return isExploding; }
	
	//make the class abstract
	virtual void setNonExplodingSprite()=0; // b/c I don't know what class -- with it's update function -- they want to use
	//~ virtual void setExplodingSprite(){}; // they could override if they wanted a different explosion strategy, but i not need 

	
protected:
	Drawable* nonExplodingSprite; // has to be a pointer so we can change it later
	Drawable* explodingSprite;

private:
	bool isExploding;
	
};

// todo: don't make copy constructor, and just make the vector of pointers to 
// if I did make a copy constructor, I would have to add callConstructor() virtual funct to drawable, and call it here when doing the copy constructor
 
#endif
