#ifndef VECTOR2D_H
#define VECTOR2D_H
class vector3D
{
  public:
    float x;
    float y;
    vector3D();
    vector3D(float _x,float _y);
    vector3D& operator=(const vector3D &rhs);
    const vector3D operator+(const vector3D &other) const ;
    const vector3D operator-(const vector3D &other) const ;
    const vector3D operator*(const float &other) const ;
    float mag();
};
#endif
