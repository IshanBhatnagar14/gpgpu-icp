#include "matrix.hh"

Matrix::Matrix(size_t width, size_t height)
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

std::vector<float> &Matrix::operator[](size_t i)
{
    return this->matrix_[i];
}
