#pragma once

#include <list>

class Point3f {
public:
  float x;
  float y;
  float z;
};

class Points {
private:
  std::vector<Point3f> points;
};
