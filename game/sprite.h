#ifndef SPRITE__H
#define SPRITE__H
#include <string>
#include "drawable.h"

class Sprite : public Drawable {
	
public:
  Sprite(const std::string&);
  Sprite(const Sprite&);
  virtual ~Sprite() { } 
  Sprite& operator=(const Sprite&);

  virtual const TextureWrapper* getFrame() const { return frame; }
  void   setFrame( const  TextureWrapper* f ) { frame = f; }

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  
private:
  const TextureWrapper * frame;
  int getDistance(const Sprite*) const;
  
};
#endif
