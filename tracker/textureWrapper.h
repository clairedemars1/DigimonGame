#ifndef FRAME__H
#define FRAME__H

#include <iostream>
#include <string>
#include <SDL.h>

class TextureWrapper {
public:
  TextureWrapper( SDL_Texture*);
  TextureWrapper(const TextureWrapper&);
  TextureWrapper& operator=(const TextureWrapper&);

  void draw(int x, int y) const;
  void draw(int x, int y, float scaleFactor) const; // new
  void draw(int x, int y, bool flip) const; //new
  void draw(int sx, int sy, int dx, int dy) const;

  SDL_Texture* getTexture() const { return texture; }
  int getWidth()  const { return width; }
  int getHeight() const { return height; }
private:
  SDL_Renderer * renderer;
  SDL_Texture * texture;
  int width;
  int height;
  TextureWrapper();
};

#endif
