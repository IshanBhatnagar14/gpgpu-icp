#pragma once

#include <variant>
#include <vector>

#include "matrix.hh"
#include "points.hh"

typedef std::vector<std::variant<float, Matrix, Vect3f>> alignment_t;

Points apply_alignment(Points p, Points model);

Vect3f get_mean(Points points);
Points create_prime(Points p, Vect3f mu);
Matrix get_quaternion_matrix(Points Pprime, Points Yprime);
Matrix get_rotation_matrix(Matrix q);
float get_scaling_factor(Points Pprime, Points Yprime);
Vect3f get_transational_offset(Vect3f mu_p, Vect3f mu_y, Matrix R);
float residual_error(const Points p, const Points y, Matrix sr, Vect3f t);
void dump_on_file(Points points, std::string path);
