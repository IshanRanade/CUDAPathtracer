#pragma once

#include <globals.h>


enum GeometryType {
	SPHERE,
	PLANE,
	TRIANGLE
};


struct Ray {
	glm::vec3 origin;
	glm::vec3 direction;
};

struct Geometry {
	enum GeometryType geometryType;
	int materialId;
	glm::mat4 transform;
	glm::mat4 inverseTransform;
	glm::mat4 inverseTranspose;
};
