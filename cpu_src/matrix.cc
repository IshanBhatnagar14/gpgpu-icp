#include "matrix.hh"

#include <iostream>

Matrix::Matrix(size_t width, size_t height)
    : width_(width)
    , height_(height)
{
    for (size_t i = 0; i < width; i++) {
        std::vector<float> row;
        matrix_.push_back(row);
        for (size_t j = 0; j < height; j++) {
            matrix_[i].push_back(0);
        }
    }
}

Matrix::Matrix(size_t size)
    : Matrix(size, size)
{
}

Matrix::Matrix(matrix_t m)
{
    matrix_ = m;
}

size_t Matrix::getWidth() const
{
    return width_;
}

size_t Matrix::getHeight() const
{
    return height_;
}

std::vector<float> &Matrix::operator[](size_t i)
{
    return this->matrix_[i];
}

std::vector<float> Matrix::operator[](size_t i) const
{
    return this->matrix_[i];
}

Matrix operator*(const Matrix &m1, const Matrix &m2)
{
    Matrix result(3);

    size_t N = m1.getWidth();

    if (m1.getHeight() == N && m2.getWidth() == N && m2.getHeight() == N) {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                result[i][j] = 0;
                for (size_t k = 0; k < N; k++) {
                    result[i][j] += m1[i][k] * m2[j][k];
                }
            }
        }
    }
    return result;
}

std::ostream &operator<<(std::ostream &os, const Matrix &m)
{
    for (size_t i = 0; i < m.getHeight(); i++) {
        os << std::endl << "[ ";
        for (size_t j = 0; j < m.getWidth(); j++) {
            os << m[i][j] << " ";
        }
        os << "]";
    }
    return os;
}
