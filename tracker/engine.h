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


class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
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
  std::vector<Patroller> patrollers;
  Player player;
  Hud hud;

  bool makeVideo;
  FrameGenerator frameGenerator;


  void draw() const;
  void update(Uint32 ticks);

};
