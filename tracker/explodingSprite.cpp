#include <iostream>
#include <cmath>
#include "explodingSprite.h"
#include "unpack.h"

ExplodingSprite::ExplodingSprite(const Sprite& s) :
  Sprite(s),
  chunks(), 
  freeList(),
  isExploding_var(false)
  
  {
  makeChunks(
    Gamedata::getInstance().getXmlInt(s.getName()+"/chunk/size")
  );
}

// copy constructor copies the basic thing, but resets any explosion that might be in process when the copy is made
ExplodingSprite::ExplodingSprite(const ExplodingSprite& rhs): 
	Sprite(rhs),
	chunks(),
	freeList(),
	isExploding_var(false)
	{
	  makeChunks(
		Gamedata::getInstance().getXmlInt(rhs.getName()+"/chunk/size")
	  );
	}

ExplodingSprite::~ExplodingSprite() { 
  for ( auto c : chunks ) delete c;
  for ( auto f : freeList ) delete f;
  chunks.clear();     // clearing a vector is a waste of time, but ...
  freeList.clear();   // still ...
}

void ExplodingSprite::draw() const { 
  // Override draw; use the draw in Chunk, which derives from Sprite.
  // So the draw we're using is actually in Sprite
  for ( Chunk* c : chunks ) {
    c->draw();
  }
}

void ExplodingSprite::setPosition(const Vector2f& pos) {
	
	if ( isExploding() ){
		std::cout << "Error: can't set exploding sprite's position during an explosion" << std::endl;
	} else {
		Sprite::setPosition(pos);
		
		// chunks
		unsigned int n = Gamedata::getInstance().getXmlInt(getName()+"/chunk/size");
		// Break the SDL_Surface into n*n squares; where each square
		// has width and height of frameWidth/n and frameHeight/n
		int chunk_width = std::max(1u, getFrame()->getWidth()/n);
		int chunk_height = std::max(1u, getFrame()->getHeight()/n);

		// Read the SDL_Surface so we can chunk it:
		int source_y = 0;
		int source_x = 0;
		//~ std::cout << "chunk count" << chunkCount() << std::endl;
		auto chunk_it = chunks.begin();
		int counter = 0;
		  // instead of making a new chunk, just change the x and y
		for(unsigned int i=0; i<n; i++){
			for (unsigned int j=0; j<n; j++){
				(*chunk_it)->setPosition(  Vector2f( getX()+source_x, getY()+source_y )  );	
				chunk_it++;
				counter++;
				source_y += chunk_height;
			}
			source_x += chunk_width;
		}
		//~ std::cout << "did I set pos of all chunks? (should be 81) " <<  (counter ) << std::endl;
	
	}
}


void ExplodingSprite::update(Uint32 ticks) {
  if (not isExploding_var) isExploding_var = true; // update only gets called when we're exploding
  std::list<Chunk*>::iterator ptr = chunks.begin();
  while (ptr != chunks.end()) {
    (*ptr)->update(ticks);
    if ((*ptr)->goneTooFar()) {  // Check to see if we should free a chunk
      freeList.push_back(*ptr);
      ptr = chunks.erase(ptr);
    }   
    else ++ptr;
  }
  if ( chunkCount() == 0) {
	  // say we're done and swap the lists (constant time)
	  isExploding_var = false;
	  chunks.swap(freeList);
  }
}

void ExplodingSprite::makeChunks(unsigned int n) { 
  // Break the SDL_Surface into n*n squares; where each square
  // has width and height of frameWidth/n and frameHeight/n
  int chunk_width = std::max(1u, getFrame()->getWidth()/n);
  int chunk_height = std::max(1u, getFrame()->getHeight()/n);
  int speedx = static_cast<int>(getVelocityX()); // Wanna test for zero...
  int speedy = static_cast<int>(getVelocityY()); // Make sure it's an int.
  if (speedx == 0) speedx = 1; // Make sure it's not 0;
  if (speedy == 0) speedy = 1; // Make sure it's not 0;

  const TextureWrapper* proto = getFrame();

  // Read the SDL_Surface so we can chunk it:
  int source_y = 0;
  while  (source_y+chunk_height < getFrame()->getHeight() ) {
    int source_x = 0;
    while ( source_x+chunk_width < getFrame()->getWidth() ) {
      // Give each chunk it's own speed/direction:
      float sx = (rand() % speedx + 40) * (rand()%2?-1:1); // 'cause %0 is 
      float sy = (rand() % speedy + 40) * (rand()%2?-1:1); // float except

      TextureWrapper* frame = proto->crop({source_x,source_y,chunk_width,chunk_height});
      Chunk* chunk = new Chunk(
                Vector2f(getX()+source_x,   // x coord of destination 
                         getY()+source_y),  // y coord of destination
                Vector2f(sx, sy),
                getName(),
                frame);
      chunks.push_back(chunk);
      source_x += chunk_width;
    }
    source_y += chunk_height;
  }
}

