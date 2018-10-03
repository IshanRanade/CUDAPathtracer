#pragma once

#include "geometry/shape.cuh"
#include <vector>


class Scene {
public:
    std::vector<Shape*> shapes;

    void initialize();
};