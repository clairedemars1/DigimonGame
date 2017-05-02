#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "background.h"
#include "player.h"
#include "patroller.h"
#include "hud.h"
#include "viewport.h"
#include "frameGenerator.h"
#include "sound.h"
#include "collisionStrategy.h"


class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
  bool getIsInGodMode(){return isInGodMode; }
  Engine(const Engine&)=delete;
  Engine& operator=(const Engine&)=delete;

private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;
  SDLSound sound;


  SDL_Renderer * const renderer;
  std::vector<Background> backgrounds;
  Viewport& viewport;

  std::vector<Drawable*> fallers;
  std::vector<Patroller*> patrollers; // pointers so we don't need to define a copy constructor just to put them in a vector (reserve and emplace_back does work alternatively, but this compiler refuses to accept that)
  Player player;
  bool isInGodMode;
  Hud hud;
  CollisionStrategy* strategy_p; // pointer so can change stategies


  bool makeVideo;
  FrameGenerator frameGenerator;


  void draw() const;
  void update(Uint32 ticks);

};
