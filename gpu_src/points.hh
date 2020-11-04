#pragma once

#include <string>
#include <vector>

#include "matrix.hh"

class Vect3f
{
  public:
    Vect3f(float x, float y, float z);
    Vect3f();
    float x;
    float y;
    float z;
    float &operator[](size_t i);
    friend std::ostream &operator<<(std::ostream &os, const Vect3f &v);
};

Vect3f operator+(const Vect3f &v1, const Vect3f &v2);
Vect3f operator-(const Vect3f &v1, const Vect3f &v2);

typedef std::vector<Vect3f> vec_p;

class Points
{
  private:
    vec_p points_;

  public:
    Points(std::string path);
    Points();
    void addPoint(Vect3f v);
    size_t size() const;
    float* convert_to_f() const;
    Points(float *f, size_t s);

    Vect3f operator[](size_t i) const;
    Vect3f &operator[](size_t i);
};

Points operator*(const Matrix &matrix, const Points &p);
Points operator+(const Points &p, const Vect3f translation);
Points &operator+=(Points &p, const Vect3f translation);
std::ostream &operator<<(std::ostream &os, const Points &p);
