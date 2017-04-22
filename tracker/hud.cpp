#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "ioMod.h"
#include "hud.h"
#include "gamedata.h"

Hud::Hud( SDL_Renderer* r):
	rend(r), 
	rect{
		Gamedata::getInstance().getXmlInt("hud/x"), 
		Gamedata::getInstance().getXmlInt("hud/y"), 
		Gamedata::getInstance().getXmlInt("hud/width"), 
		Gamedata::getInstance().getXmlInt("hud/height"),
		}, 
	lines(),
	doDraw(450)
	{}

// shows the hud for the next 350 ticks
void Hud::show() { doDraw = 350; }


void Hud::draw() const {
	if (doDraw) {
		
		// box
		Gamedata& gamedata = Gamedata::getInstance();
		SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(rend, 247, 220, 150, 255/2); // hud fill
		//~ rgb(247, 220, 150)
		SDL_RenderFillRect( rend, &rect);
		//~ SDL_SetRenderDrawColor( rend, 180, 130, 20, 255 ); // hud outline
		SDL_SetRenderDrawColor( rend,
								gamedata.getXmlInt("font/red"),
								gamedata.getXmlInt("font/green"),
								gamedata.getXmlInt("font/blue"),
								255), // hud outline
		SDL_RenderDrawRect( rend, &rect);
		
		// text
		int text_height = 15;
		int margin = 15;
		int spacer = 5;
		//~ TTF_SizeText
		//~ int text_height = TTF_FontLineSkip(font);

		IOmod& iomod = IOmod::getInstance();
		iomod.setFontSize(text_height);
		
		int y = rect.y;
		for (std::string line: lines ){
			iomod.writeText(line, rect.x + margin, y + margin);
			y += text_height + spacer;
		}
		iomod.reSetFontSize();
	
	}
	
}


void Hud::update() {
	
	
	
	if (doDraw > 0) doDraw--;
	
	// reset everything, since some stuff (the fps, elapsed time) changes
	lines.erase(lines.begin(), lines.end());
	
	// new stuff
	Clock& clock = Clock::getInstance();
	addLine("Avg fps: " + std::to_string( clock.getAvgFps() ) );
	addLine("Elapsed Secs: " + std::to_string( (int) clock.getSecondsSinceStart() ) );
	addLine("ASDW Movement"); 
	addLine("(Note: he cannot move ");
	addLine("above the water line)"); 
	
	


	
}
