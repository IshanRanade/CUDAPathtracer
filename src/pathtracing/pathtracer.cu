#include "pathtracer.cuh"

#include <vector>
#include <iostream>
#include <cuda.h>
#include "scene/camera.cuh"
#include "scene/scene.cuh"

PathTracer::PathTracer(int width, int height) :
    imageWidth(width), imageHeight(height) {
}

__global__
void test(int n, float *x, Camera *camera) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;

    //camera->w = 5;
    
    for(int i = index; i < n; i += stride) {
        x[3*i] = 200.0f;
        x[3*i+1] = 200.0f;
        x[3*i+2] = 200.0f;
    }
}

std::vector<float> PathTracer::getFrameBuffer() {
    Scene *scene = new Scene();
    Camera *camera = new Camera();

    int numPixels = imageWidth * imageHeight;
    int dataSize = numPixels * 3;

    float *x;
    cudaMallocManaged(&x, dataSize * sizeof(float));
    cudaMallocManaged(&camera, sizeof(camera));

    int blockSize = 256;
    int numBlocks = (numPixels + blockSize - 1) / blockSize;
    test<<<numBlocks,blockSize>>>(numPixels, x, camera);

    cudaDeviceSynchronize();

    std::vector<float> result = std::vector<float>(x, x + dataSize);

    cudaFree(x);

    std::cout << "done" << std::endl;
    //std::cout << camera->w << std::endl;

    //std::vector<float> result = std::vector<float>(3 * imageWidth * imageHeight);
    return result;
}
