#ifndef POINTMASS_H
#define POINTMASS_H

#include "vector2d.h"
class pointMass
{
  private:
    vector2D velocity;
    vector2D acceleration;
    vector2D lastPosition;
  public:
    vector2D position;
    pointMass(vector2D);
    pointMass();
    void addForce(vector2D);
    void updatePosition(float);
    void addFriction(float);
    void updateMomentum(float);
    float x();
    float y();
};

#endif
