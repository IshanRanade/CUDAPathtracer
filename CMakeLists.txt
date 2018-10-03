cmake_minimum_required(VERSION 3.10.3)
project(pathtracer CXX CUDA)

set (CMAKE_PREFIX_PATH "C:/Qt/5.11.2/msvc2017_64")
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CUDA_NVCC_FLAGS 
    ${CUDA_NVCC_FLAGS}; 
    -dc arch=sm_60)

list(APPEND CUDA_NVCC_FLAGS_DEBUG -G -g)
set(CUDA_ATTACH_VS_BUILD_RULE_TO_CUDA_FILE ON)
set(CUDA_SEPARABLE_COMPILATION ON)  

include_directories(include)
include_directories(src)

find_package(OpenGL)

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/globals.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/ui.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/ui.cpp
)

set(CUDA_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cu
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/pathtracer.cuh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/pathtracer.cu
	${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/raytracing/ray.cuh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/raytracing/ray.cu
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/raytracing/intersection.cuh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/raytracing/intersection.cu
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/scene/camera.cuh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/scene/camera.cu
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/scene/scene.cuh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/scene/scene.cu
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/scene/transform.cuh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/scene/transform.cu
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/scene/geometry/shape.cuh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/scene/geometry/shape.cu
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/scene/geometry/sphere.cuh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/scene/geometry/sphere.cu
)

add_executable(pathtracer
    ${CUDA_SOURCES}
    ${CPP_SOURCES}
)

target_link_libraries(pathtracer Qt5::Widgets)