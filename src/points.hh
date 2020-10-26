#pragma once

#include <list>

class Point3f {
  public:
    Point3f(float x, float y, float z);
    float x;
    float y;
    float z;
};

class Points {
  private:
    std::vector<Point3f> points;

  public:
};
