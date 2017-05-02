#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <random>
#include <array>
#include <algorithm>
#include "sprite.h"
#include "faller.h"
#include "randomguy.h"
#include "gamedata.h"
#include "engine.h"
#include "shootingSprite.h"


Engine::~Engine() { 
  std::cout << "Terminating program" << std::endl;
  for (auto* p: fallers){
	  delete p;
  }
  for (auto p: patrollers){
	  delete p;
  }
  
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  sound(),
  renderer( rc->getRenderer() ),
  backgrounds(),
  viewport( Viewport::getInstance() ),
  fallers(),
  patrollers(),
  player(),
  hud(renderer),
  strategy_p(new RectangularCollisionStrategy),
  makeVideo( false ),
  frameGenerator(),
  isInGodMode( false)
{	
  // init
	  // seed rand		
	  srand(time(0));
	  
	  //backgrounds
	  const std::string arr[4] = {"4", "3", "2", "1"};
	  for (auto& num: arr){  
		backgrounds.push_back( Background("back"+num, Gamedata::getInstance().getXmlInt("back"+num+"/factor") ) );
	  }
	  
	  // fallers
	  int n = Gamedata::getInstance().getXmlInt("numOfFallingThings");
	  for (int i=0; i<n; i++){
		 fallers.push_back(new Faller("patamon"));
	  }
	  
	  // patrollers
	  int worldWidth = Gamedata::getInstance().getXmlInt("world/width");
	  int spaceBetween = Gamedata::getInstance().getXmlInt("patroller/spaceBetween");
	  //~ int numPatrollers =  worldWidth/spaceBetween; // todo put back
	  int numPatrollers =  1;
	  int dont_hit_player = Gamedata::getInstance().getXmlInt("player/startLoc/x") + 100;
	  int playerWidth = player.getFrameWidth();
	  int playerHeight = player.getFrameHeight();
	  for (int i=0; i < numPatrollers; i++){ // place them at intervals
		  patrollers.push_back(
			  new Patroller("gesomon", 
				  dont_hit_player + (i*spaceBetween)% worldWidth,
				  playerWidth,
				  playerHeight
				  )
		  );
		  player.attach(patrollers.front()); // as an observer  
	  }

	  //player
	  Viewport::getInstance().setObjectToTrack(&player);
	  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  //~ for (auto& b : backgrounds){
	//~ b.draw();  
  //~ }
  //~ for(auto s : fallers) s->draw();

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
  
  player.draw();

  for (auto& p: patrollers){
	  p->draw();
  }
  
  // hud and info
  std::stringstream strm;
  strm << Gamedata::getInstance().getXmlStr("window/title");
  io.writeText(strm.str(), 30, 440);
  hud.draw(); 

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
	
  if ( makeVideo ) frameGenerator.makeFrame();

  for (auto& b: backgrounds) b.update();
  
  for (auto& p: patrollers ) p->update(ticks);

  for(auto* s : fallers) s->update(ticks);
  player.update(ticks); 
  hud.update();
  
  viewport.update(); // always update viewport last
  
  // collisions
  for (auto it=patrollers.begin(); it < patrollers.end(); it++) {
		if ( not isInGodMode ){
			if (strategy_p->execute(**it, player) ){ // did they kill player?
			  player.explode();		  
			}
		}
		if (player.isBulletHitting(static_cast<Drawable*>( &(**it) )) ){ // did player shoot them
		  (**it).explode();
		}
  }
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
			// show hud
			if ( keystate[SDL_SCANCODE_F1] ) {
				hud.show();
			}
			//music
			if ( keystate[SDL_SCANCODE_M] ) {
				sound.toggleMusic();
			}
			// godmode
			if (keystate[SDL_SCANCODE_G] ){
				isInGodMode = not isInGodMode;
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
			
			//receive_command player: jump
			if ( keystate[SDL_SCANCODE_J] ){
                player.receive_command("jKeyDown");
			}
      } 
      if (event.type == SDL_KEYUP) {
		  //receive_command player: jump
			if ( keystate[SDL_SCANCODE_J] ){
                player.receive_command("jKeyUp");
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
