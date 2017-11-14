#include "drawable.h"
#include "textureWrapper.h"
#include "ioMod.h"
#include "viewport.h"
#include "renderContext.h"

// malloy

TextureWrapper::TextureWrapper( SDL_Texture* tex ) :
  renderer(RenderContext::getInstance()->getRenderer()),
  texture( tex ),
  rect{0,0,0,0}
{ SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h); }

TextureWrapper::TextureWrapper( const TextureWrapper& frame ) :
  renderer(frame.renderer),
  texture(frame.texture), 
  rect(frame.rect)
{ }


TextureWrapper& TextureWrapper::operator=(const TextureWrapper& rhs) {
  renderer = rhs.renderer;
  texture = rhs.texture;
  rect = rhs.rect;
  return *this;
}

void TextureWrapper::draw(int x, int y) const {
  draw(x,y,1.0f);
}

void TextureWrapper::draw(int x, int y, float scale) const {
  x -= Viewport::getInstance().getX();
  y -= Viewport::getInstance().getY();
  int tempHeight = scale*rect.h;
  int tempWidth = scale*rect.w;
  SDL_Rect dest = {x, y, tempWidth, tempHeight};
  SDL_RenderCopy(renderer, texture, &rect, &dest);
}

void TextureWrapper::draw(int x, int y, bool flip) const { // so you can't scale a bidirectional sprite, b/c they use diff functions
  SDL_RendererFlip sdl_flip = SDL_FLIP_NONE;
  if (flip) sdl_flip = SDL_FLIP_HORIZONTAL;
  
  x -= Viewport::getInstance().getX();
  y -= Viewport::getInstance().getY();
  SDL_Rect dest = {x, y, rect.w, rect.h };
  SDL_RenderCopyEx(renderer, texture, NULL, &dest, 0, NULL, sdl_flip);
}

void TextureWrapper::draw(int sx, int sy, int dx, int dy) const {
  SDL_Rect src = { sx, sy, rect.w, rect.h };    
  SDL_Rect dst = { dx, dy, rect.w, rect.h };
  SDL_RenderCopy(renderer, texture, &src, &dst);
}

TextureWrapper* TextureWrapper::crop(SDL_Rect sub)const{
  if(sub.x+sub.w > rect.w || sub.y+sub.h > rect.h){
    std::cerr << "Attempted to crop image with invalid geometry."
              << std::endl
              << "(0,0 + "<<rect.w << "x"<<rect.h<<")"
              << " --> "
              << "("<<sub.x<<","<<sub.y<<" + "<<sub.w << "x"<<sub.h<<")"
              << std::endl;
    return nullptr;
  }

  TextureWrapper* cloned = new TextureWrapper(*this);
  cloned->rect = sub;

  return cloned;
}

