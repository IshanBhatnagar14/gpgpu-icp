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

Points &operator*(const Points &points, const &Matrix matrix)
{
    for (size_t i = 0; i < points.size(); i++) {
        size_t x = points[i].x;
        size_t y = points[i].y;
        size_t z = points[i].z;
        points[i].x = x * matrix[0][0] + y * matrix[0][1] + z * matrix[0][2];
        points[i].y = x * matrix[1][0] + y * matrix[1][1] + z * matrix[1][2];
        points[i].z = x * matrix[2][0] + y * matrix[2][1] + z * matrix[2][2];
    }
    return points;
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
