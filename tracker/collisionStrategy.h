#include <cmath>
#include "drawable.h"

#ifndef COLLISION_STRATEGY_H
#define COLLISION_STRATEGY_H

class CollisionStrategy {
public:
  virtual bool execute(const Drawable&, const Drawable&) const;
  virtual bool execute_helper(const Drawable&, const Drawable&) const=0;
  virtual void draw() const = 0;
  virtual ~CollisionStrategy() {}
};

class RectangularCollisionStrategy : public CollisionStrategy {
public:
  RectangularCollisionStrategy() {}
  virtual bool execute_helper(const Drawable&, const Drawable&) const;
  virtual void draw() const;
};

class MidPointCollisionStrategy : public CollisionStrategy {
public:
  MidPointCollisionStrategy() {}
  virtual bool execute_helper(const Drawable&, const Drawable&) const;
  virtual void draw() const;
  float distance(float, float, float, float) const;
};

#endif
