#pragma once

#include <string>
#include <vector>

class Vect3f
{
  public:
    Vect3f(float x, float y, float z);
    friend std::ostream &operator<<(std::ostream &os, const Vect3f &v);
    float x;
    float y;
    float z;
};

typedef std::vector<Vect3f> vec_p;

class Points
{
  private:
    vec_p points_;

  public:
    Points(std::string path);
    Points();
    void addPoint(Vect3f v);
    size_t size();
    Vect3f &operator[](int i);
};
