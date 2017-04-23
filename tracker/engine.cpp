#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <random>
#include <array>
#include <algorithm>
#include "sprite.h"
#include "faller.h"
#include "player.h"
#include "randomguy.h"
#include "gamedata.h"
#include "engine.h"

Engine::~Engine() { 
  std::cout << "Terminating program" << std::endl;
  for (auto* it: fallers){
	  delete it;
  }

}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  backgrounds(),
  viewport( Viewport::getInstance() ),
  fallers(),
  player(),
  hud(renderer),
  makeVideo( false ),
  frameGenerator()
{		
  //backgrounds
  const std::string arr[4] = {"4", "3", "2", "1"};
  for (auto& num: arr){  
	backgrounds.push_back( Background("back"+num, Gamedata::getInstance().getXmlInt("back"+num+"/factor") ) );
  }
  
  //things falling from sky
  int n = Gamedata::getInstance().getXmlInt("numOfFallingThings");
  std::srand( std::time(0) ); // important for spawning
  for (int i=0; i<n; i++){
	 fallers.push_back(new Faller("patamon"));
  }
  //~ std::sort(fallers.begin(), fallers.end(), // decided to do another way
		//~ [](const Drawable* a, const Drawable* b)->bool{return a->getScaleFactor() < b->getScaleFactor();} // why fail when Faller*? 
  //~ );
  
  //player
  Viewport::getInstance().setObjectToTrack(&player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  //~ for (auto& b : backgrounds){
	//~ b.draw();  
  //~ }
  
  //backgrounds alternated with fallers
  backgrounds[0].draw();
  for (auto faller: fallers){
	  if (faller->getScaleFactor() < 1.0 ) faller->draw();
  }
  
  backgrounds[1].draw();
  for (auto faller: fallers){
	  if (faller->getScaleFactor() > 0.4 && faller->getScaleFactor() < 1.0 ) faller->draw();
  }
  backgrounds[2].draw();
  
  backgrounds[3].draw();
  for (auto faller: fallers){
	  if (faller->getScaleFactor() == 1.0 ) faller->draw();
  }
  
  //~ for(auto s : fallers) s->draw();
  player.draw();
  
  // hud and info
  std::stringstream strm;
  strm << Gamedata::getInstance().getXmlStr("screenTitle");
  io.writeText(strm.str(), 30, 440);
  hud.draw(); 

  viewport.draw();
  SDL_RenderPresent(renderer);
}

//~ void Engine::update(Uint32 ticks,  const std::array<char, 2> &directions) {
void Engine::update(Uint32 ticks) {
	
  if ( makeVideo ) frameGenerator.makeFrame();

  for (auto& b: backgrounds) b.update();

  for(auto* s : fallers) s->update(ticks);
  //~ player.update(ticks, directions); 
  player.update(ticks); 
  hud.update();
  
  viewport.update(); // always update viewport last
}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();

  /// event loop
  while ( !done ) {
	

	/// while a key has been released or pressed, and we haven't attended to it yet
    while ( SDL_PollEvent(&event) ) {
		
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      
      if(event.type == SDL_KEYDOWN) {	
			// quit
			if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
			  done = true;
			  break;
			}
			
			// pause
			if ( keystate[SDL_SCANCODE_P] ) {
			  if ( clock.isPaused() ) clock.unpause();
			  else clock.pause();
			}
			if ( keystate[SDL_SCANCODE_F1] ) {
				hud.show();
			}
			
			// capture frames
			if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
			  std::cout << "Initiating frame capture" << std::endl;
			  makeVideo = true;
			}
			else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
			  std::cout << "Terminating frame capture" << std::endl;
			  makeVideo = false;
			}
			
			//notify player: jump
			if ( keystate[SDL_SCANCODE_J] ){
				player.notify("jKeyDown");
			}
      } 
      if (event.type == SDL_KEYUP) {
		  //notify player: jump
			if ( keystate[SDL_SCANCODE_J] ){
				player.notify("jKeyUp");
			}
	  }

    } // end while
    
	
	// redraw frame & update sprite positions for the next draw
    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {

      clock.incrFrame();
      draw();
      update(ticks);
    }
  } /// end event loop
}
