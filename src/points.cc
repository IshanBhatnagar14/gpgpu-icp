#include "points.hh"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "log.hh"

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
