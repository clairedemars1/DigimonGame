#ifndef FRAME__H
#define FRAME__H
// malloy

#include <iostream>
#include <string>
#include <SDL.h>

class TextureWrapper {
public:
  TextureWrapper( SDL_Texture* );
  TextureWrapper(const TextureWrapper&);
  TextureWrapper& operator=(const TextureWrapper&);

  ~TextureWrapper()=default;

  void draw(int x, int y) const;
  void draw(int x, int y, float scale) const;
  void draw(int x, int y, bool flip) const; // from claire's
  void draw(int sx, int sy, int dx, int dy) const;

  SDL_Texture* getTexture() const { return texture; }
  inline int getWidth()  const { return rect.w; }
  inline int getHeight() const { return rect.h; }

  TextureWrapper* crop(SDL_Rect)const;
private:
  SDL_Renderer * renderer;
  SDL_Texture * texture;
  SDL_Rect rect;
  TextureWrapper();
};

#endif
