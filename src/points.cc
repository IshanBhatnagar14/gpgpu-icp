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

    std::vector<Vect3f> points;

    std::ifstream file(path);

    std::string line = "";
    while (getline(file, line, '\n')) {
        std::cout << "line:" << line << std::endl;

        std::vector<std::string> vect;
        std::stringstream line_stream(line);
        while (line_stream.good()) {
            std::string value;
            getline(line_stream, value, ',');
            vect.push_back(value);
        }

        Vect3f v(std::stof(vect[0]), 0, 0);
        //std::cout << v;
        points.push_back(v);
    }

    file.close();
}

std::vector<Vect3f> Points::getPoints() const
{
    return points;
}

std::ostream &operator<<(std::ostream &os, const Vect3f &v)
{
    os << "{ x:" << v.x << ", y:" << v.y << ", z:" << v.z << "}" << std::endl;

    return os;
}

Vect3f::Vect3f(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Points::add_point(Vect3f v)
{
    this->points.push_back(v);
}
