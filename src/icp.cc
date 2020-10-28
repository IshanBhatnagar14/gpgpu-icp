#include <limits.h>
#include <math.h>

#include "points.hh"

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