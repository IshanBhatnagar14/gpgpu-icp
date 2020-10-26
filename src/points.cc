#include "points.hh"

Vect3f::Vect3f(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Points::add_point(Vect3f v)
{
    this->points.push_back(v);
}
