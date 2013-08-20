#include "vector3d.h"
#include "math.h"

vector3D::vector3D()
{
  x = y = z = 0.0;
}

vector3D::vector3D(float _x,float _y, float _z)
{
  x = _x; y = _y; z = _z;
}
vector3D& vector3D::operator=(const vector3D &rhs) 
{
  x = rhs.x; y = rhs.y; z = rhs.z;
  return *this;
}
const vector3D vector3D::operator+(const vector3D &other) const 
{
  vector3D result = *this;
  result.x = x + other.x;
  result.y = y + other.y;
  result.z = z + other.z;
  return result;
}
const vector3D vector3D::operator-(const vector3D &other) const 
{
  vector3D result = *this;
  result.x = x - other.x;
  result.y = y - other.y;
  result.z = z - other.z;
  return result;
}
const vector3D vector3D::operator*(const float &other) const 
{
  vector3D result = *this; 
  result.x *= other;     
  result.y *= other;
  result.z *= other;
  return result;
}
float vector3D::mag()
{
  return sqrt(x*x+y*y+z*z);
}
