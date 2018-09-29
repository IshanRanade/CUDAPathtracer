#pragma once

#include "../../../globals.h"
#include "../../raytracing/ray.cuh"
#include "../../raytracing/intersection.cuh"
#include "../transform.cuh"


class Shape {
public:
    Transform transform;

    virtual bool Intersect(const Ray &ray, Intersection *isect) const = 0;
    virtual void InitializeIntersection(Intersection* isect, float t, Point3f pLocal) const;
    virtual void ComputeTBN(const Point3f& P, Normal3f* nor, Vector3f* tan, Vector3f* bit) const = 0;
    virtual float Area() const = 0;
};