#include "icp.hh"

#include <limits.h>
#include <math.h>

//s, R, t, err
alignment_t find_alignment(Points scene, Points model)
{
    alignment_t alignment;

    Vect3f mu_scene = get_mean(scene);
    Vect3f mu_model = get_mean(model);

    Points scene_prime = create_prime(scene, mu_scene);
    Points model_prime = create_prime(model, mu_model);

    Matrix quaternion = get_quaternion_matrix(scene_prime, model_prime);

    float scale = get_scaling_factor(scene_prime, model_prime);
    Matrix rotation = get_rotation_matrix(quaternion);
    Vect3f translation =
        get_transational_offset(mu_scene, mu_model, scale, rotation);
    float error = 0;

    alignment.push_back(scale);
    alignment.push_back(rotation);
    alignment.push_back(translation);
    alignment.push_back(error);

    return alignment;
}

std::vector<size_t> find_correspondences(Points scene, Points model)
{
    size_t size_s = scene.size();
    size_t size_m = model.size();

    std::vector<size_t> correspondences;

    for (size_t i = 0; i < size_s; i++) {
        Vect3f s_point = scene[i];
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

/* Points apply_alignment(Points scene, Points moddel, std::vector<size_t> correspondences)
{
    size_t size_s = scene.size();

    float scale =

    for (size_t i = 0; i < size_s; i++)
    {
        Vect3f s_point = scene[i];
    }
}*/
