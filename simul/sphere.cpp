#include "sphere.h"

sphere::sphere(vector3D pos, float r)
{
  centre = pos;
  radius = r;
}

vector3D sphere::resolve(vector3D x)
{
  vector3D diff = x-centre;
  if (diff.mag()>radius)
    return x;
  return centre + diff*(radius/diff.mag());
}
