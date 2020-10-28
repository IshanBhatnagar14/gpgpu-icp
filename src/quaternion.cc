#include "matrix.hh"
#include "points.hh"

float getSum(Points Pprime, size_t P_idx, Points Yprime, size_t Y_idx)
{
    float sum = 0;
    for (size_t i = 0; i < Pprime.size(); i++)
        sum += Pprime[i][P_idx] * Yprime[i][Y_idx];

    return sum;
}

Matrix getNmatrix(Points Pprime, Points Yprime)
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
