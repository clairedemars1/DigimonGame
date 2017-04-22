cmake_minimum_required(VERSION 3.6)
project(proj_4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        tracker/clock.cpp
        tracker/clock.h
        tracker/drawable.h
        tracker/engine.cpp
        tracker/engine.h
        tracker/textureWrapper.cpp
        tracker/textureWrapper.h
        tracker/frameFactory.cpp
        tracker/frameFactory.h
        tracker/frameGenerator.cpp
        tracker/frameGenerator.h
        tracker/gamedata.cpp
        tracker/gamedata.h
        tracker/player.cpp
        tracker/player.h
        tracker/hud.cpp
        tracker/hud.h
        tracker/ioMod.cpp
        tracker/ioMod.h
        tracker/main.cpp
        tracker/multisprite.cpp
        tracker/multisprite.h
        tracker/parseXML.cpp
        tracker/parseXML.h
        tracker/randomguy.cpp
        tracker/randomguy.h
        tracker/renderContext.cpp
        tracker/renderContext.h
        tracker/sprite.cpp
        tracker/sprite.h
        tracker/twowaymultisprite.cpp
        tracker/twowaymultisprite.h
        tracker/unpack.cpp
        tracker/unpack.h
        tracker/vector2f.cpp
        tracker/vector2f.h
        tracker/viewport.cpp
        tracker/viewport.h
        tracker/background.cpp
        tracker/background.h
        old_engine.cpp)

add_executable(proj_4 ${SOURCE_FILES})