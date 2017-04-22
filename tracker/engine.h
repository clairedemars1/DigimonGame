#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "background.h"
#include "player.h"
#include "hud.h"
#include "viewport.h"
#include "frameGenerator.h"

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

  SDL_Renderer * const renderer;
  std::vector<Background> backgrounds;
  Viewport& viewport;

  std::vector<Drawable*> fallers;
  Player player;
  Hud hud;

  bool makeVideo;
  FrameGenerator frameGenerator;


  void draw() const;
  //~ void update(Uint32 ticks, const std::array<char, 2> &directions);
  void update(Uint32 ticks);

};
