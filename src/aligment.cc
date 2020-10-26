#include "aligment.hh"

Vect3f mean(Points points)
{
    Vect3f m(0,0,0);
    vec_p v = points.getPoints();
    size_t s = v.size();
    for (size_t i = 0; i < s; i++)
    {
       m.x += v[i].x; 
       m.y += v[i].y; 
       m.z += v[i].z; 
    }
    m.x /= s;
    m.y /= s;
    m.z /= s;
    
    return m;
}
