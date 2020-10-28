#include "aligment.hh"
#include "log.hh"

#include <iostream>
Vect3f mean(Points points)
{
    Vect3f m(0, 0, 0);
    size_t s = points.size();
    for (size_t i = 0; i < s; i++) 
    {
        m.x += points[i].x;
        m.y += points[i].y;
        m.z += points[i].z;
    }
    m.x /= s;
    m.y /= s;
    m.z /= s;

    return m;
}


Points create_prime(Points p, Vect3f m)
{
    Points r = Points();
    for (size_t i = 0; i < p.size(); i++) 
    {
        Vect3f tmp (p[i].x - m.x, p[i].y - m.y, p[i].z - m.z);
        r.addPoint(tmp);
    }
    return r;
}

void find_aligment(Points p, Points y)
{
    Log l("Align");

    Vect3f m_p(mean(p));
    
    Points p_prime = create_prime(p, m_p);


    p = y; //a supprimer cest pour enlever les warnings
}
