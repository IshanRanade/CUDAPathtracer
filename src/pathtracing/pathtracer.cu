#include "pathtracer.cuh"

#include <vector>
#include <iostream>
#include <thrust/random.h>
#include <globals.h>


PathTracer::PathTracer(int width, int height) :
    imageWidth(width), imageHeight(height) {
}

struct Camera {
	int x;

	/*__device__ void dos() {
		x++;
	}*/
};

__global__
void testCameraKernel(Camera* camera) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    //int stride = blockDim.x * gridDim.x;

	if (index == 0) {
		//camera->dos();
		printf("%i", camera->x);
	}

    //camera->w = 5;
    
    //for(int i = index; i < n; i += stride) {
    //    x[3*i] = 200.0f;
    //    x[3*i+1] = 200.0f;
    //    x[3*i+2] = 200.0f; 
    //}
}

__global__ void doNothingKernel() {

}

std::vector<float> PathTracer::getFrameBuffer() {
	//doNothingKernel << <1, 1 >> > ();
	//return std::vector<float>();

	Camera * testCamera = new Camera();
	cudaMallocManaged(&testCamera, sizeof(Camera));
	testCameraKernel << <1, 1 >> > (testCamera);
	return std::vector<float>();


	//testCamera->x = 5;

	//return;

	//Scene *scene = new Scene();
    //Camera *camera = new Camera();

    //int numPixels = imageWidth * imageHeight;
    //int dataSize = numPixels * 3;

    //float *x;
    //cudaMallocManaged(&x, dataSize * sizeof(float));
    //cudaMallocManaged(&camera, sizeof(camera));

    //int blockSize = 256;
    //int numBlocks = (numPixels + blockSize - 1) / blockSize;
    //test<<<numBlocks,blockSize>>>();

	//Camera *camera = new Camera();
	//cudaMallocManaged(&camera, sizeof(Camera));

	//camera->x = 6;
	//std::cout << camera->x << std::endl;
	
	//test<< <numBlocks, blockSize >> > (camera);

    //cudaDeviceSynchronize();

	

    //std::vector<float> result = std::vector<float>(x, x + dataSize);

    //cudaFree(x);

    //std::cout << "done" << std::endl;
    //std::cout << camera->w << std::endl;

    //std::vector<float> result = std::vector<float>(3 * imageWidth * imageHeight);
    //return std::vector<float>();
}
