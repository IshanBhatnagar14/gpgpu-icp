#include <iostream>
#include <cmath>

#include "icp.hh"
#include "log.hh"

Vect3f get_mean(Points points)
{
    Vect3f m(0, 0, 0);
    size_t s = points.size();
    for (size_t i = 0; i < s; i++) {
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
    for (size_t i = 0; i < p.size(); i++) {
        Vect3f tmp(p[i].x - m.x, p[i].y - m.y, p[i].z - m.z);
        r.addPoint(tmp);
    }
    return r;
}

Matrix get_rotation_matrix(Matrix q)
{
    float q0 = q[0][0];
    float q1 = q[0][1];
    float q2 = q[1][0];
    float q3 = q[1][1];

    std::vector<float> Qb0 = { q0, q1, q2, q3 };
    std::vector<float> Qb1 = { -q1, q0, -q3, q2 };
    std::vector<float> Qb2 = { -q2, q3, q0, -q1 };
    std::vector<float> Qb3 = { -q3, -q2, q1, q0 };

    std::vector<float> Q0 = { q0, -q1, -q2, -q3 };
    std::vector<float> Q1 = { q1, q0, -q3, q2 };
    std::vector<float> Q2 = { q2, q3, q0, -q1 };
    std::vector<float> Q3 = { q3, -q2, q1, q0 };

    matrix_t QB_tmp = { Qb0, Qb1, Qb2, Qb3 };
    matrix_t Q_tmp = { Q0, Q1, Q2, Q3 };

    Matrix Q(Q_tmp);
    Matrix QB(QB_tmp);
    Matrix r(4, 4);

    for (size_t i = 0; i < 4; i++) 
        for (size_t j = 0; j < 4; j++) 
        {
            r[i][j] = 0;
            for (size_t k = 0; k < 4; k++) 
                r[i][j] += QB[i][k] * Q[k][j];
        }

    Matrix r3(3, 3);

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            r3[i][j] = r[1 + i][1 + j];

    return r3;
}

float getSum(Points Pprime, size_t P_idx, Points Yprime, size_t Y_idx)
{
    float sum = 0;
    for (size_t i = 0; i < Pprime.size(); i++)
        sum += Pprime[i][P_idx] * Yprime[i][Y_idx];

    return sum;
}

Matrix get_quaternion_matrix(Points Pprime, Points Yprime)
{
    float s_xx = getSum(Pprime, 0, Yprime, 0);
    float s_xy = getSum(Pprime, 0, Yprime, 1);
    float s_xz = getSum(Pprime, 0, Yprime, 2);

    float s_yx = getSum(Pprime, 1, Yprime, 0);
    float s_yy = getSum(Pprime, 1, Yprime, 1);
    float s_yz = getSum(Pprime, 1, Yprime, 2);

    float s_zx = getSum(Pprime, 2, Yprime, 0);
    float s_zy = getSum(Pprime, 2, Yprime, 1);
    float s_zz = getSum(Pprime, 2, Yprime, 2);

    Matrix N(4);
    N[0][0] = s_xx + s_yy + s_zz;
    N[0][1] = s_yz - s_zy;
    N[0][2] = s_zx - s_xz;
    N[0][3] = s_xy + s_yx;

    N[1][0] = s_yz - s_zy;
    N[1][1] = s_xx - s_zz - s_yy;
    N[1][2] = s_xy + s_yx;
    N[1][3] = s_xz + s_zx;

    N[2][0] = s_zx - s_xz;
    N[2][1] = s_yx + s_xy;
    N[2][2] = s_yy - s_zz - s_xx;
    N[2][3] = s_yz + s_zy;

    N[3][0] = s_xy - s_yx;
    N[3][1] = s_zx + s_xz;
    N[3][2] = s_zy + s_yz;
    N[3][3] = s_zz + s_yy - s_xx;

    return N;
}

float get_scaling_factor(Points Pprime, Points Yprime)
{
    float sp = 0;
    float d = 0;
    for (size_t i = 0; i < Yprime.size(); i++)
    {
        d += Yprime[i].x * Yprime[i].x + Yprime[i].y * Yprime[i].y 
           + Yprime[i].z * Yprime[i].z;
        sp += Pprime[i].x * Pprime[i].x + Pprime[i].y * Pprime[i].y 
            + Pprime[i].z * Pprime[i].z;       
    }
    return std::sqrt(d/sp);
}

Vect3f get_transational_offset(Vect3f mu_p, Vect3f mu_y, float s, Matrix R)
{
    return Vect3f(0, 0, 0);
}

/*
   void find_aligment(Points p, Points y)
   {
   Log l("Align");

   Vect3f m_p(mean(p));

   Points p_prime = create_prime(p, m_p);


   p = y; //a supprimer cest pour enlever les warnings
   }*/
