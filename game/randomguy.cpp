#include <iostream>
#include "engine.h"
#include "randomguy.h"


void RandomGuy::update(Uint32 ticks){
		
	  advanceFrame(ticks);
	  	  
	  switch(whichPhase){
		  case 3:
		  case 4: {	
			moveVert(ticks);
			break;
	  }
	  lastPhase = whichPhase;

	}
}
