#ifndef SPHERE_H
#define SPHERE_H
#include "vector2d.h"

class sphere
{
  private:
    vector2D centre;
    float radius;
  public:
    sphere(vector2D,float);
    vector2D resolve(vector2D);

};

#endif
