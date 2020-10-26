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

typedef std::vector<Vect3f> vec_p;

class Points {
  private:
    vec_p points;

  public:
    Points(std::string path);
    vec_p getPoints() const;
    friend std::ostream &operator<<(std::ostream &os, const Vect3f &v);
    void add_point(Vect3f v);
};
