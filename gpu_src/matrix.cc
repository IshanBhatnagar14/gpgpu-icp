#include "matrix.hh"

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
