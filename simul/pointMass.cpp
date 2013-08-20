#include "pointMass.h"

pointMass::pointMass(vector2D ps)
{
  position = ps;
  velocity = vector2D(0,0);
  acceleration = vector2D(0,0);
}

pointMass::pointMass()
{
  position = vector2D(0,0);
  velocity = vector2D(0,0);
  acceleration = vector2D(0,0);
}

void pointMass::addForce(vector2D f)
{
  acceleration = acceleration + f;
}

void pointMass::calculatePosition(float dt)
{
  velocity = velocity + acceleration * dt;
  position = position + velocity * dt;
  acceleration = vector2D(0,0);
}
