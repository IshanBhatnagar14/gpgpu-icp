#pragma once

#include <ostream>
#include <vector>

typedef std::vector<std::vector<float>> matrix_t;

class Matrix
{
  private:
    matrix_t matrix_;
    size_t width_;
    size_t height_;

  public:
    Matrix(size_t size);
    Matrix(matrix_t m);
    Matrix(size_t width, size_t height);

    size_t getWidth() const;
    size_t getHeight() const;

    std::vector<float> operator[](size_t i) const;
    std::vector<float> &operator[](size_t i);
    friend std::ostream &operator<<(std::ostream &os, const Matrix &m);
};

Matrix operator*(const Matrix &m1, const Matrix &m2);
