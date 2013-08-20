#include "vector2d.h"
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
    void enforce();
};
