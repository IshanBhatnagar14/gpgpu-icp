#include "aligment.hh"

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


Points create_prime(Points p)
{
    Points r = Points();
    for (size_t i = 0; i < p.size(); i++) 
    {
        
    }
    return r;
}


void find_aligment(Points p, Points y)
{
    p = y;
    
}