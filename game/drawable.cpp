#include "drawable.h"
#include <iostream>
#include <string>

void Drawable::keepInWorld(){
  if ( getY() < 0) {
    setY(0);
  }
  if ( getY() > worldHeight-frameHeight) {
    setY(worldHeight-frameHeight);
  }

  if ( getX() < 0) {
	  setX(0);
  }
  if ( getX() > worldWidth-frameWidth) {
		setX(worldWidth-frameWidth);
  }  
}

