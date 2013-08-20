class vector2D
{
  public:
    float x;
    float y;
    vector2D();
    vector2D(float _x,float _y);
    vector2D& operator=(const vector2D &rhs);
    const vector2D operator+(const vector2D &other) const ;
    const vector2D operator-(const vector2D &other) const ;
    const vector2D operator*(const float &other) const ;
    float mag();
};
