#pragma once

#include <vector>

/*
    This encapsulates all the logic for path tracing.  It exposes a primary public function, getFrameBuffer(),
    that uses its set values to path trace and image and return a buffer with the color values of the pixels
    in the image.
*/
class PathTracer {
public:
    PathTracer(int width, int height);
    std::vector<float> getFrameBuffer();


private:
    int imageWidth;
    int imageHeight;
};
