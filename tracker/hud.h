#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "drawable.h"
#include "clock.h"



class Hud { //not responsible for the memory it points to
	public:
		Hud(SDL_Renderer* r);
		void draw() const;
		void update();
		void show();

	private:
		SDL_Renderer* rend;
		SDL_Rect rect;
		std::vector<std::string> lines;
		int doDraw; // pos if hud should be displayed, zero otherwise, decremented so hud times out
		void addLine(const std::string t) {lines.push_back(t);}
		Hud(Hud&);
		Hud& operator=(const Hud& lhs);

};	

