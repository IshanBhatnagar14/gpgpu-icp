#pragma once

#include <vector>

typedef std::vector<std::vector<float>> matrix_t;

class Matrix
{
  private:
    matrix_t matrix_;

  public:
    Matrix(size_t size);
    Matrix(size_t width, size_t height);
};
