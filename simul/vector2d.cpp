#include "vector2d.h"
#include "math.h"

vector2D::vector2D()
{
  x = y = 0.0;
}

vector2D::vector2D(float _x,float _y)
{
  x = _x; y = _y;
}
vector2D& vector2D::operator=(const vector2D &rhs) 
{
  x = rhs.x; y = rhs.y;
  return *this;
}
const vector2D vector2D::operator+(const vector2D &other) const 
{
  vector2D result = *this;
  result.x = x + other.x;
  result.y = y + other.y;
  return result;
}
const vector2D vector2D::operator*(const float &other) const 
{
  vector2D result = *this; 
  result.x *= other;     
  result.y *= other;
  return result;
}
float vector2D::mag()
{
  return sqrt(x*x+y*y);
}
