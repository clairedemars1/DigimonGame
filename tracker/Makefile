CXX = g++

# Warnings frequently signal eventual errors:
CXXFLAGS=`sdl2-config --cflags` -g -W -Wall -std=c++11 -Weffc++ -Wextra -pedantic -O0 -I `sdl2-config --prefix`/include/

LDFLAGS = `sdl2-config --libs` -lm -lexpat -lSDL2_ttf -lSDL2_image -lSDL2_mixer

OBJS = \
	renderContext.o \
	ioMod.o \
	drawable.o \
	parseXML.o \
	gamedata.o \
	viewport.o \
	background.o \
	unpack.o \
	textureWrapper.o \
	frameFactory.o \
	frameGenerator.o \
	hud.o \
	sprite.o \
	multisprite.o \
	twowaymultisprite.o \
	twowayexplodingmultisprite.o \
	shootingSprite.o \
	playernonexploding.o \
	player.o\
	patroller.o \
	faller.o\
	randomguy.o \
	vector2f.o \
	clock.o \
	engine.o \
	main.o \
	sound.o \
	bullet.o \
	bulletPool.o \
	collisionStrategy.o

#~ name changes: frame -> textureWrapper 
#~ goodguy -> player 
#~ world -> background
 
EXEC = run

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
	rm -rf frames/*.bmp

frames_clean:
	rm -rf frames/*.bmp
	
make_vid:
	avconv -r 30 -i frames/cmdemar.%4d.bmp frames/cmdemar.mp4


#does not pick up header files changes: eg patroller (even though patroller.o)
