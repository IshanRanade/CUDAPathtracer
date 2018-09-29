#pragma once

#include "geometry/shape.cuh"


class Scene {
public:
    std::vector<Shape*> shapes;

    void initialize();
};