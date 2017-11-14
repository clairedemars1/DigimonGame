#include <SDL.h>
#include <string>
#include <queue>

#ifndef ENGINE_H
#define ENGINE_H

class Engine;

class Clock {
public:
  static Clock& getInstance();
  unsigned int getTicks() const; // gets number of ticks since beginning of animation
  float getSecondsSinceStart() const;
  int getFramesSinceStart() const;
  int getAvgFps() const;


private:
  friend class Engine;

  bool started;
  bool paused;

  const bool FRAME_CAP_ON;
  //~ const Uint32 maxFrameRate;
  const Uint32 PERIOD;

  unsigned int frames;

  unsigned int timeAtStart;
  unsigned int timeAtPause;
  unsigned int currTicks;
  unsigned int prevTicks;
  unsigned int ticks;
  
  int maxNumFrames;
  std::queue<unsigned int> timesOfLastXFrames;

  unsigned int getElapsedTicks(); // returns number of ticks since the last time the window was drawn (the last frame)
  void incrFrame();
  void toggleSloMo();

  bool isStarted() const { return started; }
  bool isPaused() const  { return paused;  }
  unsigned int getFrames() const  { return frames;  }
  unsigned int getSeconds() const { return getTicks()/1000;  }
  unsigned int capFrameRate() const;
  int getFps() const;

  void startClock();
  void pause();
  void unpause();

  Clock();
  Clock(const Clock&);
  Clock&operator=(const Clock&);
};

#endif
