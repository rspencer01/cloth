#ifndef POINTMASS_H
#define POINTMASS_H

#include "vector3d.h"
class pointMass
{
  private:
    vector3D velocity;
    vector3D acceleration;
    vector3D lastPosition;
  public:
    vector3D position;
    pointMass(vector3D);
    pointMass();
    void addForce(vector3D);
    void updatePosition(float);
    void addFriction(float);
    void updateMomentum(float);
    float x();
    float y();
};

#endif
