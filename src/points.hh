#pragma once

#include <string>
#include <vector>

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
    Points(std::string path);
    std::vector<Vect3f> getPoints() const;
    void add_point(Vect3f v);
};
