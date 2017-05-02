#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "drawable.h"
#include "clock.h"
#include "player.h"


// forward declare
class Engine;

class Hud { //not responsible for the memory it points to
	public:
		Hud(SDL_Renderer* r, const Player* player, const bool* _isGodP);
		void draw() const;
		void update();
		void show();

	private:
		SDL_Renderer* rend;
		SDL_Rect rect;
		std::vector<std::string> lines;
		int doDraw; // pos if hud should be displayed, zero otherwise, decremented so hud times out
		
		//information sources
		const Player* playerP;
		const bool* isGodP;
		
		void addLine(const std::string t) {lines.push_back(t);}
		
		Hud(Hud&);
		Hud& operator=(const Hud& lhs);		
		
		
		

};	

