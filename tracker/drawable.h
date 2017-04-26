#ifndef DRAWABLE__H
#define DRAWABLE__H
#include <SDL.h>
#include <iostream>
#include <string>
#include "vector2f.h"
#include "textureWrapper.h"
#include "gamedata.h"
 
// Drawable is an Abstract Base Class (ABC) that
// specifies the methods that derived classes may
// and must have.
class Drawable { // really "drawable that has a texture and velocity"
public:
  Drawable(const std::string& n, const Vector2f& pos, const Vector2f& vel, 
  int frameW, int frameH): 
    name(n), position(pos), velocity(vel),
    scaleFactor(1), 
    worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
    worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
    frameWidth(frameW),
    frameHeight(frameH)
    {}


  Drawable(const Drawable& s) : 
    name(s.name), position(s.position), velocity(s.velocity),
    scaleFactor(s.scaleFactor),
    worldWidth(s.worldWidth),
    worldHeight(s.worldHeight),
    frameWidth(s.frameWidth),
    frameHeight(s.frameHeight)
    { }

  virtual ~Drawable() {}

  virtual void draw() const = 0;
  virtual void update(Uint32 ticks) = 0;
  virtual const TextureWrapper* getFrame() const = 0;
  void keepInWorld();

  const std::string& getName() const { return name; }
  void setName(const std::string& n) { name = n;    }

  float getX() const  { return position[0]; }
  virtual void  setX(float x) { position[0] = x;    }

  float getY() const  { return position[1]; }
  void  setY(float y) { position[1] = y;    }

  float getVelocityX() const   { return velocity[0]; }
  void  setVelocityX(float vx) { velocity[0] = vx;   }
  float getVelocityY() const   { return velocity[1]; }
  void  setVelocityY(float vy) { velocity[1] = vy;   }
  const Vector2f& getVelocity() const    { return velocity; }
  void  setVelocity(const Vector2f& vel) { velocity = vel;  }
  
  const Vector2f& getPosition() const    { return position; }
  void  setPosition(const Vector2f& pos) { position = pos;  }
  
  float getScaleFactor() const { return scaleFactor; }
  void setScaleFactor(float s){  scaleFactor = s; }
  
  int getFrameWidth() const { return frameWidth; }
  int getFrameHeight() const { return frameHeight; }

private:
  std::string name;
  Vector2f position;
  Vector2f velocity;
  
protected:  
  float scaleFactor;
  int worldWidth;
  int worldHeight;
  int frameWidth; // of the single frame/textureWrapper (for Sprite) or of one of the many frames (MultiSprite)
  int frameHeight;
};


#endif
