#include "pointMass.h"

pointMass::pointMass(vector2D ps)
{
  position = ps;
  lastPosition = position;
  velocity = vector2D(0,0);
  acceleration = vector2D(0,0);
}

pointMass::pointMass()
{
  position = vector2D(0,0);
  lastPosition = position;
  velocity = vector2D(0,0);
  acceleration = vector2D(0,0);
}

void pointMass::addForce(vector2D f)
{
  acceleration = acceleration + f;
}

void pointMass::addFriction(float k)
{
  addForce(velocity * -k);
}

void pointMass::updatePosition(float dt)
{
  velocity = velocity + acceleration * dt;
  position = position + velocity * dt;
  acceleration = vector2D(0,0);
}

float pointMass::x()
{
  return position.x;
}
float pointMass::y()
{
  return position.y;
}

void pointMass::updateMomentum(float dt)
{
  velocity = (position-lastPosition)*(1.0/dt);
  lastPosition = position;
}


