#include "constraint.h"
#include <stdio.h>

constraint::constraint(pointMass* a, pointMass* b, float d, float _k)
{
  pointA = a;
  pointB = b;
  length = d;
  k = _k;
}

void constraint::enforce()
{
  vector2D diff = pointA->position-pointB->position;
  if (diff.mag()<length)
    return;
  diff = diff - diff * (length/diff.mag());
  pointA->addForce(diff * - k);
  pointB->addForce(diff *   k);
}
