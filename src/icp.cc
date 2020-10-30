#include "icp.hh"

#include <fstream>
#include <limits.h>
#include <math.h>

#include "log.hh"

#define MAX_ITER 2
#define THRESH 0.00001

//s, R, t, err
alignment_t find_alignment(Points p, Points y, Points m)
{
    Log l(__FUNCTION__);
    alignment_t alignment;

    Vect3f mu_p = get_mean(p);
    l << "mu p: " << mu_p << std::endl;
    Vect3f mu_y = get_mean(m);
    l << "mu y: " << mu_y << std::endl;

    Points p_prime = create_prime(p, mu_p);
    l << "p prime: " << p_prime << std::endl;
    Points y_prime = create_prime(y, mu_y);
    l << "y prime: " << y_prime << std::endl;
    l << "primes ok" << std::endl;

    Matrix quaternion = get_quaternion_matrix(p_prime, y_prime);
    l << "quaternion: " << quaternion << std::endl;

    float scale = get_scaling_factor(p_prime, y_prime);
    l << "Scale: " << scale << std::endl;
    Matrix rotation = get_rotation_matrix(quaternion);
    l << "Rotation: " << rotation << std::endl;

    Matrix scaled_rotation(3);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            scaled_rotation[i][j] = rotation[i][j] * scale;

    l << "Rotation * scale: " << scaled_rotation << std::endl;

    Vect3f translation = get_transational_offset(mu_p, mu_y, scaled_rotation);
    l << "Translation: " << translation << std::endl;
    float error = residual_error(p, y, scaled_rotation, translation);
    l << "Residual error: " << error << std::endl;

    alignment.push_back(scale);
    alignment.push_back(rotation);
    alignment.push_back(scaled_rotation);
    alignment.push_back(translation);
    alignment.push_back(error);

    return alignment;
}

std::vector<size_t> find_correspondences(Points p, Points model)
{
    size_t size_s = p.size();
    size_t size_m = model.size();

    std::vector<size_t> correspondences;

    for (size_t i = 0; i < size_s; i++) {
        Vect3f s_point = p[i];
        float min_dist = LONG_MAX;
        size_t chosen_idx = -1;

        for (size_t j = 0; j < size_m; j++) {
            Vect3f m_point = model[j];
            float dist = sqrt(pow(m_point.x - s_point.x, 2) +
                              pow(m_point.y - s_point.y, 2) +
                              pow(m_point.z - s_point.y, 2));

            if (dist < min_dist) {
                min_dist = dist;
                chosen_idx = j;
            }
        }
        correspondences.push_back(chosen_idx);
    }
    return correspondences;
}

void apply_scale(Points &p, float scale)
{
    size_t s_size = p.size();

    for (size_t i = 0; i < s_size; i++) {
        p[i].x *= scale;
        p[i].y *= scale;
        p[i].z *= scale;
    }
}

void apply_scalled_rotation(Points &p, Matrix scalled_rotation)
{
    p = scalled_rotation * p;
}

void apply_translation(Points &p, Vect3f translation)
{
    size_t s_size = p.size();

    for (size_t i = 0; i < s_size; i++) {
        p[i].x += translation.x;
        p[i].y += translation.y;
        p[i].z += translation.z;
    }
}

//s; R; t
Points apply_alignment(Points p, Points model)
{
    size_t s_size = p.size();

    Log l("Alignment");

    float final_scale = 1;
    Matrix final_rotation(3);
    Vect3f final_translation(0, 0, 0);
    float final_err = 0;

    for (size_t iter = 0; iter < MAX_ITER; iter++) {
        l.title();

        std::vector<size_t> correspondences = find_correspondences(p, model);

        Points y;
        for (size_t i = 0; i < model.size(); i++) {
            y.addPoint(model[correspondences[i]]);
        }

        alignment_t alignment = find_alignment(p, y, model);

        float scale = std::get<float>(alignment[0]);
        Matrix rotation = std::get<Matrix>(alignment[1]);
        Matrix scalled_rotation = std::get<Matrix>(alignment[2]);
        Vect3f translation = std::get<Vect3f>(alignment[3]);
        float err = std::get<float>(alignment[4]);

        final_scale *= scale;
        final_translation.x += translation.x;
        final_translation.y += translation.y;
        final_translation.z += translation.z;

        apply_scalled_rotation(p, scalled_rotation);
        apply_translation(p, translation);

        Vect3f e;

        for (size_t i = 0; i < s_size; i++) {
            e.x = y[i].x - p[i].x;
            e.y = y[i].y - p[i].y;
            e.z = y[i].z - p[i].z;
            err += e.x * e.x + e.y * e.y + e.z * e.z;
        }

        final_err = err / s_size;
        l << "Error: " << final_err << std::endl;

        if (final_err < THRESH) {
            break;
        }
        dump_on_file(p, "result" + std::to_string(iter) + ".txt");
    }
    l.title();
    l << "Final scale: " << final_scale << std::endl;
    l << "Final rotation: TODO" << std::endl;
    l << "Final translation: " << final_translation << std::endl;
    l << "Final error: " << final_err << std::endl;

    dump_on_file(p, "result.txt");

    return p;
}

void dump_on_file(Points p, std::string path)
{
    Log l(__FUNCTION__);
    l << "Dump result on " << path << " | p_size:" << p.size() << std::endl;

    std::ofstream stream;
    stream.open(path);
    stream << "Points_0,Points_1,Points_2\n";

    for (size_t i = 0; i < p.size(); i++)
        stream << p[i].x << "," << p[i].y << "," << p[i].z << "\n";

    stream.close();
}
