#include "icp.hh"

#include <fstream>
#include <math.h>
#include <iostream>
#include <cstdio>
#include <ctime>

#include "log.hh"

#define MAX_ITER 16
#define THRESH 0.00001


std::clock_t start_timer() {
    return std::clock();
}

double stop_timer(std::clock_t start) {
    return (std::clock() - start) / (double) CLOCKS_PER_SEC;
}

//s, R, t, err
alignment_t find_alignment(Points p, Points y)
{

    Log l("Find Alignment");
    alignment_t alignment;

    Vect3f mu_p = get_mean(p);
    l << "mu p: " << mu_p << std::endl;
    Vect3f mu_y = get_mean(y);
    l << "mu y: " << mu_y << std::endl;

    Points p_prime = create_prime(p, mu_p);
    //l << "p prime: " << p_prime << std::endl;
    Points y_prime = create_prime(y, mu_y);
    //l << "y prime: " << y_prime << std::endl;
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

Points get_correspondences(const Points p, const Points m)
{


    Points Y;
    size_t size = p.size();

    for (size_t i = 0; i < size; i++) {
        Vect3f pi = p[i];
        float minD = std::numeric_limits<float>::max();
        size_t idx = 0;

        for (size_t k = 0; k < size; k++) {
            Vect3f mk = m[k];

            float dist = (sqrt(pow(pi.x - mk.x, 2) + pow(pi.y - mk.y, 2) +
                               pow(pi.z - mk.z, 2)));

            if (dist < minD) {
                minD = dist;
                idx = k;
            }
        }

        Y.addPoint(m[idx]);
    }
    return Y;
}

//s; R; t
Points apply_alignment(Points p, const Points model)
{
    size_t size = p.size();

    Log l("Alignment");

    float final_scale = 1;
    Matrix final_rotation(3);
    Vect3f final_translation(0, 0, 0);
    float final_err = 0;

    for (size_t iter = 0; iter < MAX_ITER; iter++) {
        l.title(iter + 1);

        auto clk = start_timer();
        // Compute Y
        Points y = get_correspondences(p, model);

        std::cout << "Time Elapsed:" << stop_timer(clk) <<"\n";

        clk = start_timer();

        // Find Alignment
        alignment_t alignment = find_alignment(p, y);

        std::cout << "Time Elapsed:" << stop_timer(clk) <<"\n";


        float scale = std::get<float>(alignment[0]);
        Matrix rotation = std::get<Matrix>(alignment[1]);
        Matrix scalled_rotation = std::get<Matrix>(alignment[2]);
        Vect3f translation = std::get<Vect3f>(alignment[3]);
        float err = std::get<float>(alignment[4]);

        // Saving final results
        final_scale *= scale;
        final_translation = final_translation + translation;

        // Applying (newP)
        Points newP = (scalled_rotation * p) + translation;

        // Error
        Vect3f e;

        for (size_t i = 0; i < size; i++) {
            e = y[i] - newP[i];
            err += e.x * e.x + e.y * e.y + e.z * e.z;
        }
        err /= size;
        l << "Error: " << err << std::endl;

        // Saving error
        final_err = err;

        if (final_err < THRESH) {
            break;
        }

        dump_on_file(newP, "result" + std::to_string(iter) + ".txt");

        // Applying to p
        p = newP;
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
    Log l("Dump on File");
    l << "Dump result on " << path << " | p_size:" << p.size() << std::endl;

    std::ofstream stream;
    stream.open(path);
    stream << "Points_0,Points_1,Points_2\n";

    for (size_t i = 0; i < p.size(); i++)
        stream << p[i].x << "," << p[i].y << "," << p[i].z << "\n";

    stream.close();
}
