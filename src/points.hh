#pragma once

#include <list>

class Vector3f {
public:
  float x;
  float y;
  float z;
};

class Points {
private:
  std::vector<Vector3f> points;
};
