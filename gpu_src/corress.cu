#include <cstdio>
#include <cuda.h>

#include "icp.hh"

#define MAX_FLOAT 3.40282e+038

__global__ void search_corres(const float *p, const float *m, float *y,
                              size_t s)
{
    int i = (blockDim.x * blockIdx.x + threadIdx.x) * 3;
    if (i >= s)
        return;
    float pi[3] = { p[i], p[i + 1], p[i + 2] };

    float minD = MAX_FLOAT;
    size_t idx = 0;

    for (size_t k = 0; k < s; k += 3) {
        float mk[3] = { m[k], m[k + 1], m[k + 2] };

        float dist = (sqrt(pow(pi[0] - mk[0], 2) + pow(pi[1] - mk[1], 2) +
                           pow(pi[2] - mk[2], 2)));

        if (dist < minD) {
            minD = dist;
            idx = k;
        }
    }
    y[i] = m[idx];
    y[i + 1] = m[idx + 1];
    y[i + 2] = m[idx + 2];
}

Points get_correspondences(const Points p, const Points m)
{
    size_t size_malloc = p.size() * sizeof(float) * 3;

    float *cm, *cp, *cy, *arr_y, *arr_m, *arr_p;

    arr_p = p.convert_to_f();
    arr_m = m.convert_to_f();
    arr_y = (float *)std::malloc(size_malloc);

    cudaMalloc((void **)&cp, size_malloc);
    cudaMalloc((void **)&cm, size_malloc);
    cudaMalloc((void **)&cy, size_malloc);

    cudaMemcpy(cp, arr_p, size_malloc, cudaMemcpyHostToDevice);
    cudaMemcpy(cm, arr_m, size_malloc, cudaMemcpyHostToDevice);

    search_corres<<<ceil(p.size() / 1024), 1024>>>(cp, cm, cy, p.size() * 3);
    cudaDeviceSynchronize();

    cudaMemcpy(arr_y, cy, size_malloc, cudaMemcpyDeviceToHost);

    Points y(arr_y, p.size());

    free(arr_p);
    free(arr_m);
    free(arr_y);
    cudaFree(cp);
    cudaFree(cm);
    cudaFree(cy);

    return y;
}
