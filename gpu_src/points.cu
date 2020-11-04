#include <algorithm>
#include <fstream>
#include <iterator>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "log.hh"
#include "points.hh"

/*
** Points
*/

Points::Points(std::string path)
{
    Log l("Parsing");
    l << "Loading " << path << std::endl;

    std::ifstream file(path);

    std::string line = "";

    // Skip first line
    getline(file, line, '\n');

    while (getline(file, line, '\n')) {
        std::vector<std::string> vect;
        std::stringstream line_stream(line);
        while (line_stream.good()) {
            std::string value;
            getline(line_stream, value, ',');
            vect.push_back(value);
        }

        Vect3f v(std::stof(vect[0]), std::stof(vect[1]), std::stof(vect[2]));
        this->addPoint(v);
    }

    file.close();
}

Points::Points()
{
}

void Points::addPoint(Vect3f v)
{
    this->points_.push_back(v);
}

size_t Points::size() const
{
    return this->points_.size();
}

Vect3f Points::operator[](size_t i) const
{
    return this->points_[i];
}

Vect3f &Points::operator[](size_t i)
{
    return this->points_[i];
}

Points operator*(const Matrix &matrix, const Points &p)
{
    Points newP;
    for (size_t i = 0; i < p.size(); i++) {
        float x = p[i].x;
        float y = p[i].y;
        float z = p[i].z;
        newP.addPoint(
            Vect3f(x * matrix[0][0] + y * matrix[0][1] + z * matrix[0][2],
                   x * matrix[1][0] + y * matrix[1][1] + z * matrix[1][2],
                   x * matrix[2][0] + y * matrix[2][1] + z * matrix[2][2]));
    }
    return newP;
}

Points operator+(const Points &p, const Vect3f translation)
{
    Points newP;
    size_t s_size = p.size();

    for (size_t i = 0; i < s_size; i++) {
        newP.addPoint(p[i] + translation);
    }

    return newP;
}

/*
** Vect3f
*/

Vect3f::Vect3f(float x, float y, float z)
    : x{ x }
    , y{ y }
    , z{ z }
{
}

Vect3f::Vect3f()
    : Vect3f(0, 0, 0)
{
}

float &Vect3f::operator[](size_t i)
{
    switch (i % 3) {
    case 0:
        return x;
    case 1:
        return y;
    default:
        return z;
    }
}

Vect3f operator+(const Vect3f &v1, const Vect3f &v2)
{
    return Vect3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vect3f operator-(const Vect3f &v1, const Vect3f &v2)
{
    return Vect3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

/*
** Dump
*/

std::ostream &operator<<(std::ostream &os, const Vect3f &v)
{
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

std::ostream &operator<<(std::ostream &os, const Points &p)
{
    for (size_t i = 0; i < p.size(); i++) {
        os << std::endl << p[i];
    }
    return os;
}

float *Points::convert_to_f() const
{
    size_t size = this->size();
    size_t array_size = 3 * size;

    float *f = (float *)std::malloc(sizeof(float) * array_size);

    for (size_t i = 0; i < size; i++) {
        size_t j = 3 * i;
        f[j] = this->points_[i].x;
        f[j + 1] = this->points_[i].y;
        f[j + 2] = this->points_[i].z;
    }
    return f;
}

Points::Points(float *f, size_t s)
{
    Vect3f v(0, 0, 0);

    for (size_t i = 0; i < s * 3; i += 3) {
        v.x = f[i];
        v.y = f[i + 1];
        v.z = f[i + 2];

        this->addPoint(v);
    }
}
