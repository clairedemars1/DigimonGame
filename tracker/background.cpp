#include <iostream>
#include "background.h"
#include "renderContext.h"

Background::Background(const std::string& name, int fact) :
  frame( RenderContext::getInstance()->getFrame(name) ),
  factor(fact),
    worldWidth( Gamedata::getInstance().getXmlInt("world/width") ),
    frameWidth( frame->getWidth() ),
    viewX(0.0), viewY(0.0), 
    view(Viewport::getInstance()) 
{ }

void Background::update() {
  viewX = static_cast<int>(view.getX() / factor) % frameWidth;
  viewY = view.getY();
}

void Background::draw() const {
  frame->draw(0,0,-viewX,-viewY);
  frame->draw(0,0,frameWidth-viewX,-viewY);
}

