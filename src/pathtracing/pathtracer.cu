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

__global__ void fillPBO(int n, uchar4 *pbo, float frame) {
	int index = blockIdx.x * blockDim.x + threadIdx.x;

	if (index < n) {
		pbo[index].w = 0;
		pbo[index].x = 0;
		pbo[index].y = 0;
		pbo[index].z = (int)frame;
	}
}

void PathTracer::pathtrace(void *pbo, float frame) {
	//std::cout << frame << std::endl;
	int blockSize = 256;
	int numBlocks = (imageWidth * imageHeight + blockSize - 1) / blockSize;

	fillPBO<<<numBlocks,blockSize>>>(imageWidth * imageHeight, (uchar4*)pbo, frame);
	cudaDeviceSynchronize();

	return;


	//doNothingKernel << <1, 1 >> > ();
	//return std::vector<float>();

	//Camera * testCamera = new Camera();
	//cudaMallocManaged(&testCamera, sizeof(Camera));
	//testCameraKernel << <1, 1 >> > (testCamera);
	//return std::vector<float>();
	//return;

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
