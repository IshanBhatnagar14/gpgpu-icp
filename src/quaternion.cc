#include "computation.hh"
#include "matrix.hh"

float getSum(Points Pprime, int P_idx, Points Yprime, int Y_idx)
{
    float sum = 0;
    for (int i = 0; i < Pprime.size(); i++)
        sum += Pprime[i][P_idx] * Yprime[i][Yprime];

    return sum;
}

Matrix getNmatrix(Points Pprime, Points Yprime)
{
    s_xx = getSum(Pprime, 1, Yprime, 1);
    s_xy = getSum(Pprime, 1, Yprime, 2);
    s_xz = getSum(Pprime, 1, Yprime, 3);

    s_yx = getSum(Pprime, 2, Yprime, 1);
    s_yy = getSum(Pprime, 2, Yprime, 2);
    s_yz = getSum(Pprime, 2, Yprime, 3);

    s_zx = getSum(Pprime, 3, Yprime, 1);
    s_zy = getSum(Pprime, 3, Yprime, 2);
    s_zz = getSum(Pprime, 3, Yprime, 3);

    Matrix N(4);
    N[0][0] = s_xx + s_yy + s_zz;
    N[0][1] = s_yz - s_zy;
    N[0][2] = s_zx - s_xz;
    N[0][3] = s_xy + s_yx;

    N[1][0] = s_yz - s_zy;
    N[1][1] = s_xx - s_zz - syy;
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
