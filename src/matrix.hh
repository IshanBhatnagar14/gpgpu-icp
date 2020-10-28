#pragma once

#include <vector>

typedef std::vector<std::vector<float>> matrix_t;

class Matrix
{
  private:
    matrix_t matrix_;

  public:
    Matrix(size_t size);
    Matrix(matrix_t m);
    Matrix(size_t width, size_t height);

    std::vector<float> &operator[](size_t i);
};
