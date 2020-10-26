#pragma once

#include <list>

class Vect3f {
  public:
    Vect3f(float x, float y, float z);
    float x;
    float y;
    float z;
};

class Points {
  private:
    std::vector<Vect3f> points;

  public:
    void add_point(Point3f p);
};
