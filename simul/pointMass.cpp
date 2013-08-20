#include "pointMass.h"

pointMass::pointMass(vector3D ps)
{
  position = ps;
  lastPosition = position;
  velocity = vector3D(0,0);
  acceleration = vector3D(0,0);
}

pointMass::pointMass()
{
  position = vector3D(0,0);
  lastPosition = position;
  velocity = vector3D(0,0);
  acceleration = vector3D(0,0);
}

void pointMass::addForce(vector3D f)
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
  acceleration = vector3D(0,0);
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


