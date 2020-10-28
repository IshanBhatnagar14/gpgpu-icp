#include "aligment.hh"
#include "matrix.hh"
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

Matrix rotation_computation(Matrix q)
{
    float q0 = q[0][0];
    float q1 = q[0][1];
    float q2 = q[1][0];
    float q3 = q[1][1];


    std::vector<float> Qb0 = {q0, -q1, -q2, -q3};
    std::vector<float> Qb1 = {q1,  q0,  q3, -q2};
    std::vector<float> Qb2 = {q2, -q3,  q0,  q1};
    std::vector<float> Qb3 = {q3,  q2, -q1,  q0};

    std::vector<float> Q0 = {q0, -q1, -q2, -q3};
    std::vector<float> Q1 = {q1,  q0, -q3,  q2};
    std::vector<float> Q2 = {q2,  q3,  q0, -q1};
    std::vector<float> Q3 = {q3, -q2,  q1,  q0};

    matrix_t QB = {Qb0, Qb1, Qb2, Qb3};
    matrix_t Q = {Q0, Q1, Q2, Q3};
    
    Matrix r(Q);

    return r;
}


void find_aligment(Points p, Points y)
{
    Log l("Align");

    Vect3f m_p(mean(p));
    
    Points p_prime = create_prime(p, m_p);


    p = y; //a supprimer cest pour enlever les warnings
}
