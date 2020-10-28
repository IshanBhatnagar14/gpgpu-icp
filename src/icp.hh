#pragma once

#include "matrix.hh"
#include "points.hh"

Vect3f get_mean(Points points);
Matrix get_quaternion_matrix(Points Pprime, Points Yprime);
Matrix get_rotation_matrix(Matrix q);
float get_scaling_factor(Points Pprime, Points Yprime);
Vect3f get_transational_offset(Vect3f mu_y, Vect3f mu_p, float s, Matrix R);
