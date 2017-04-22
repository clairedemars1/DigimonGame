#include "multisprite.h"

#ifndef TWOWAYMULTISPRITE_H
#define TWOWAYMULTISPRITE_H
 
class TwoWayMultiSprite : public MultiSprite {
	public:
		
		TwoWayMultiSprite(const std::string&);
		TwoWayMultiSprite(const TwoWayMultiSprite&);
		//~ void update(Uint32 ticks); // I can't change this to get bidirectionality to work, b/c it's going to be overwritten by the derived classes for specific sprites (note: I'm surprised I don't need to declare update here, and say that it's also virtual for twowaymultisprite
		// therefore need to change another function that always gets called (or make a new one and call it from main)
		// I'll use draw() so I can use SDL's built in flipping
		void draw() const;
};
#endif
