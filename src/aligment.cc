#include "points.hh"

Vect3f mean(Points p)
{
    Vect3f m(0,0,0);
    size_t s = p.points.size();
    for (size_t i = 0; i < s; i++)
    {
       m.x += p[i].x; 
       m.y += p[i].y; 
       m.z += p[i].z; 
    }
    m.x /= s;
    m.y /= s;
    m.z /= s;
}
