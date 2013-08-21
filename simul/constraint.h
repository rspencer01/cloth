#ifndef CONSTRAINT_H
#define CONSTRAINT_H
#include "vector3d.h"
#include "pointMass.h"

class constraint
{
  private:
    pointMass* pointA;
    pointMass* pointB;
    float length;
    float k;
    bool broken;
  public:
    constraint(pointMass*,pointMass*,float,float);
    bool enforce();
};
#endif
