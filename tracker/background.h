#include <string>
#include "textureWrapper.h"
#include "viewport.h"

class Background {
public:
  Background(const std::string& name, int fact);
  // ~Background() { } // The frame will be deleted by the FrameFactory
  void update();
  void draw() const;
private:
  TextureWrapper* const frame;
  int factor;
  unsigned worldWidth;
  unsigned frameWidth;
  float viewX;
  float viewY;
  const Viewport & view;
  //~ Background(const Background&); // need this to fill a vector with backgrounds. shallow copy is good b/c only pointer is to a frame, a resource managed by another class
  //~ Background& operator=(const Background&);
};
