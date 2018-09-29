#pragma once

#include "la.h"

typedef float Float;
typedef glm::vec3 Color3f;
typedef glm::vec3 Normal3f;
typedef glm::vec2 Point2f;
typedef glm::vec3 Point3f;
typedef glm::ivec2 Point2i;
typedef glm::ivec3 Point3i;
typedef glm::vec2 Vector2f;
typedef glm::vec3 Vector3f;
typedef glm::ivec2 Vector2i;
typedef glm::ivec3 Vector3i;
typedef glm::mat4 Matrix4x4;
typedef glm::mat3 Matrix3x3;

// Global constants. You may not end up using all of these.
static const float ShadowEpsilon = 0.0001f;
static const float RayEpsilon = 0.000005f;
static const float Pi = 3.14159265358979323846;
static const float TwoPi = 6.28318530717958647692;
static const float InvPi = 0.31830988618379067154;
static const float Inv2Pi = 0.15915494309189533577;
static const float Inv4Pi = 0.07957747154594766788;
static const float PiOver2 = 1.57079632679489661923;
static const float PiOver4 = 0.78539816339744830961;
static const float Sqrt2 = 1.41421356237309504880;
static const float OneMinusEpsilon = 0.99999994;