#include "sphere.h"

sphere::sphere(vector2D pos, float r)
{
  centre = pos;
  radius = r;
}

vector2D sphere::resolve(vector2D x)
{
  vector2D diff = x-centre;
  if (diff.mag()>radius)
    return x;
  return centre + diff*(radius/diff.mag());
}
