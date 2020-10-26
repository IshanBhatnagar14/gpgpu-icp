#include "points.hh"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "log.hh"

Points::Points(std::string path)
{
    Log l(__FUNCTION__);
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
        addPoint(v);
    }

    file.close();
}

std::vector<Vect3f> Points::getPoints() const
{
    return points;
}

void Points::addPoint(Vect3f v)
{
    this->points.push_back(v);
}

Vect3f::Vect3f(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

std::ostream &operator<<(std::ostream &os, const Vect3f &v)
{
    os << "{ x:" << v.x << ", y:" << v.y << ", z:" << v.z << "}" << std::endl;

    return os;
}
