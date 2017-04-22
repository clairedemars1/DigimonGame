#include <string>
#include "twowaymultisprite.h"

class RandomGuy : public TwoWayMultiSprite{
	
public:
	RandomGuy(const std::string& name, int& whichPhase): TwoWayMultiSprite(name), whichPhase(whichPhase) {}
	
	RandomGuy(const RandomGuy
	& rhs): TwoWayMultiSprite(rhs), whichPhase(rhs.whichPhase){}
	
	void update(Uint32 ticks);

private:
	int& whichPhase;
	int lastPhase=0; // meaning previous 
	
	
};
