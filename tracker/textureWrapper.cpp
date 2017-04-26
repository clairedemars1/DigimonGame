#include "drawable.h"
#include "textureWrapper.h"
#include "ioMod.h"
#include "viewport.h"
#include "renderContext.h"

TextureWrapper::TextureWrapper( SDL_Texture* tex ) :
  renderer(RenderContext::getInstance()->getRenderer()),
  texture( tex ),
  width(0), 
  height(0)
{ SDL_QueryTexture(texture, NULL, NULL, &width, &height); }

TextureWrapper::TextureWrapper( const TextureWrapper& frame ) :
  renderer(frame.renderer),
  texture(frame.texture), 
  width(frame.width), 
  height(frame.height)
{ }


TextureWrapper& TextureWrapper::operator=(const TextureWrapper& rhs) {
  renderer = rhs.renderer;
  texture = rhs.texture;
  width = rhs.width;
  height = rhs.height;
  return *this;
}

void TextureWrapper::draw(int x, int y) const {
  x -= Viewport::getInstance().getX();
  y -= Viewport::getInstance().getY();
  SDL_Rect dest = {x, y, width, height };
  SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void TextureWrapper::draw(int x, int y, float scaleFactor) const {
  x -= Viewport::getInstance().getX();
  y -= Viewport::getInstance().getY();
  int temp_width = width*scaleFactor;
  int temp_height = height*scaleFactor;
  SDL_Rect dest = {x, y, temp_width, temp_height };
  SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void TextureWrapper::draw(int x, int y, bool flip) const { // so you can't scale a bidirectional sprite, b/c they use diff functions
  SDL_RendererFlip sdl_flip = SDL_FLIP_NONE;
  if (flip) sdl_flip = SDL_FLIP_HORIZONTAL;
  
  x -= Viewport::getInstance().getX();
  y -= Viewport::getInstance().getY();
  SDL_Rect dest = {x, y, width, height };
  SDL_RenderCopyEx(renderer, texture, NULL, &dest, 0, NULL, sdl_flip);
}

void TextureWrapper::draw(int sx, int sy, int dx, int dy) const {
  SDL_Rect src = { sx, sy, width, height };    
  SDL_Rect dst = { dx, dy, width, height };
  SDL_RenderCopy(renderer, texture, &src, &dst);
}

