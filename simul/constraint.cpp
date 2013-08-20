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

void constraint::enforce()
{
  if (broken)
    return;
  vector3D diff = pointA->position-pointB->position;
  if (diff.mag()<length)
    return;
  diff = diff - diff * (length/diff.mag());
  // Simulating breaking
  if (diff.mag()>40.0*length)
  {
    broken = true;
    return;
  }
  pointA->addForce(diff * - k);
  pointB->addForce(diff *   k);
}
