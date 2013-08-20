#include "vector2d.h"
class pointMass
{
  private:
    vector2D position;
    vector2D velocity;
    vector2D acceleration;
  public:
    pointMass(vector2D);
    pointMass();
    void addForce(vector2D);
    void calculatePosition(float);
};
