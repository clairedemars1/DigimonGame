#ifndef MULTISPRITE__H
#define MULTISPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class MultiSprite : public Drawable {
public:
  MultiSprite(const std::string&);
  MultiSprite(const std::string& name, int startX, int startY);
  MultiSprite(const MultiSprite&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const TextureWrapper* getFrame() const {
    return frames[currentFrame]; 
  }

protected:
  std::vector<TextureWrapper *> frames;
  
  void setFrames(const std::string& name);

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;

  void advanceFrame(Uint32 ticks);
  void advanceFrame();
  void moveVert(Uint32 ticks);
  void moveHoriz(Uint32 ticks);
};
#endif
