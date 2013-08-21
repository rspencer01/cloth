#include "constraint.h"
#include <stdio.h>

constraint::constraint(pointMass* a, pointMass* b, float d, float _k)
{
  pointA = a;
  pointB = b;
  length = d;
  k = _k;
  broken = false;
}

bool constraint::enforce()
{
  if (broken)
    return false;
  vector3D diff = pointA->position-pointB->position;
  if (diff.mag()<length)
    return false;
  diff = diff - diff * (length/diff.mag());
  // Simulating breaking
  if (diff.mag()>1.5*length)
  {
    broken = true;
    return true;
  }
  pointA->addForce(diff * - k);
  pointB->addForce(diff *   k);
  return false;
}
