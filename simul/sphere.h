#ifndef SPHERE_H
#define SPHERE_H
#include "vector2d.h"

class sphere
{
  private:
    float radius;
  public:
    vector2D centre;
    sphere(vector2D,float);
    vector2D resolve(vector2D);

};

#endif
