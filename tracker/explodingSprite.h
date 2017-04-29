#ifndef EXplodING_SPRITE_H
#define EXplodING_SPRITE_H

#include <vector>
#include <list>
#include "chunk.h"

class ExplodingSprite : public Sprite {
public:
  ExplodingSprite(const Sprite& s);
  ExplodingSprite(const ExplodingSprite&); // i allow

  ~ExplodingSprite();
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual void setPosition(const Vector2f& pos); // note: I'm being lazy and not overriding setX(), setY: potential bugs
  void makeChunks(unsigned int);
  unsigned int chunkCount() const { return chunks.size(); }
  unsigned int freeCount()  const { return freeList.size(); }
  //~ bool isExploding() const { return !(chunks.size() == 0 ); } // fails since as soon as chunks is empty, we fill it back up to be ready for next explosion
  bool isExploding() const { return isExploding_var; }
private:
  std::list<Chunk*> chunks; // An ExplodingSprite is a list of sprite chunks
  std::list<Chunk*> freeList; // When a chunk gets out of range it goes here
  bool isExploding_var;

  //~ ExplodingSprite(const ExplodingSprite&); // Explicit disallow (Item 6)
  ExplodingSprite& operator=(const ExplodingSprite&); // (Item 6)
};


#endif
