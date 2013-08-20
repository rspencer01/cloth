#ifndef SPHERE_H
#define SPHERE_H
#include "vector3d.h"

class sphere
{
  private:
    float radius;
  public:
    vector3D centre;
    sphere(vector3D,float);
    vector3D resolve(vector3D);

};

#endif
