#pragma once

#include "../../globals.h"


class Intersection {
public:
    Point3f point;
    Normal3f normalGeometric;
    Point2f uv;
    float t;

    Vector3f tangent, bitangent;
};
