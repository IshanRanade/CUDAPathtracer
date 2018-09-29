#pragma once

#include "../../../globals.h"
#include "shape.cuh"


class Sphere : public Shape {
public:
    virtual bool Intersect(const Ray &ray, Intersection *isect) const;
    virtual void ComputeTBN(const Point3f& P, Normal3f* nor, Vector3f* tan, Vector3f* bit) const;
    virtual float Area() const;
};