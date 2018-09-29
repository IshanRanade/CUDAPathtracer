#include "scene.cuh"

#include "geometry/sphere.cuh"


void Scene::initialize() {
    Sphere* sphere = new Sphere();
    Transform transform = Transform(glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(1,1,1));
    sphere->transform = transform;
}