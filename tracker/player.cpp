#include "player.h"
#include "playernonexploding.h"

void Player::setNonExplodingSprite(){
	delete nonExplodingSprite;
	nonExplodingSprite = new PlayerNonExploding();
}
