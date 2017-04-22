#include <string>
#include <vector>
#include <map>
#include "textureWrapper.h"
#include "gamedata.h"
#include "unpack.h"

class FrameFactory {
private:
friend class RenderContext;

  static FrameFactory* getInstance();
  ~FrameFactory();

  TextureWrapper* getFrame(const std::string&);
  std::vector<TextureWrapper*> getFrames(const std::string&);

  static FrameFactory* instance;
  const Gamedata& gdata;
  std::map<std::string, SDL_Texture*> textures;
  std::map<std::string, TextureWrapper*> frames;

  std::map<std::string, std::vector<SDL_Texture*> > multiTextures;
  std::map<std::string, std::vector<TextureWrapper*> > multiFrames;

  FrameFactory() : 
    gdata( Gamedata::getInstance() ), 
    textures(),
    frames(),
    multiTextures(),
    multiFrames()
  {}
  FrameFactory(const FrameFactory&);
  FrameFactory& operator=(const FrameFactory&);
};
