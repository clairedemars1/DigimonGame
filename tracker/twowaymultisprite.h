#include "multisprite.h"

#ifndef TWOWAYMULTISPRITE_H
#define TWOWAYMULTISPRITE_H


// also has an exploding sprite, but if you leave that field empty in the xml, it doesn't make it 

class TwoWayMultiSprite : public MultiSprite {
public:
	TwoWayMultiSprite(const std::string&); 
	TwoWayMultiSprite(const TwoWayMultiSprite&);
	//~ void update(Uint32 ticks); // I can't change this to get bidirectionality to work, b/c it's going to be overwritten by the derived classes for specific sprites (note: I'm surprised I don't need to declare update here, and say that it's also virtual for twowaymultisprite
	// therefore need to change another function that always gets called - I'll use draw - (or make a new one and call it from main)
	// I'll use draw() so I can use SDL's built in flipping
	virtual void draw() const;

	
};
#endif
