#include "icp.hh"

#include <limits.h>
#include <math.h>

#include "log.hh"

#define MAX_ITER 2
#define THRESH 0.00001

//s, R, t, err
alignment_t find_alignment(Points scene, Points model)
{
    Log l(__FUNCTION__);
    alignment_t alignment;

    Vect3f mu_scene = get_mean(scene);
    l << "mu scene: " << mu_scene << std::endl;
    Vect3f mu_model = get_mean(model);
    l << "mu model: " << mu_model << std::endl;

    Points scene_prime = create_prime(scene, mu_scene);
    l << "scene prime: " << scene_prime << std::endl;
    Points model_prime = create_prime(model, mu_model);
    l << "model prime: " << model_prime << std::endl;
    l << "primes ok" << std::endl;

    Matrix quaternion = get_quaternion_matrix(scene_prime, model_prime);
    l << "quaternion: " << quaternion << std::endl;

    float scale = get_scaling_factor(scene_prime, model_prime);
    l << "Scale: " << scale << std::endl;
    Matrix rotation = get_rotation_matrix(quaternion);
    l << "Rotation: " << rotation << std::endl;

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            rotation[i][j] *= scale;

    l << "Rotation * scale: " << rotation << std::endl;

    Vect3f translation = get_transational_offset(mu_scene, mu_model, rotation);
    l << "Translation: " << translation << std::endl;
    float error = residual_error(scene, model, rotation, translation);
    l << "Error: " << error << std::endl;

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

void apply_scale(Points &scene, float scale)
{
    size_t s_size = scene.size();

    for (size_t i = 0; i < s_size; i++) {
        scene[i].x *= scale;
        scene[i].y *= scale;
        scene[i].z *= scale;
    }
}

void apply_rotation(Points &scene, Matrix rotation)
{
    scene = rotation * scene;
}

void apply_translation(Points &scene, Vect3f translation)
{
    size_t s_size = scene.size();

    for (size_t i = 0; i < s_size; i++) {
        scene[i].x += translation.x;
        scene[i].y += translation.y;
        scene[i].z += translation.z;
    }
}

//s; R; t
Points apply_alignment(Points scene, Points model)
{
    size_t s_size = scene.size();

    Log l("Alignment");

    for (size_t iter = 0; iter < MAX_ITER; iter++) {
        l.title();

        std::vector<size_t> correspondences =
            find_correspondences(scene, model);

        Points y;
        for (size_t i = 0; i < model.size(); i++) {
            y.addPoint(model[correspondences[i]]);
        }

        alignment_t alignment = find_alignment(scene, y);

        float scale = std::get<float>(alignment[0]);
        Matrix rotation = std::get<Matrix>(alignment[1]);
        Vect3f translation = std::get<Vect3f>(alignment[2]);
        float err = std::get<float>(alignment[3]);

        apply_scale(scene, scale);
        apply_rotation(scene, rotation);
        apply_translation(scene, translation);

        err /= s_size;

        /*if (err < THRESH) {
            break;
        }*/
    }
    return scene;
}
