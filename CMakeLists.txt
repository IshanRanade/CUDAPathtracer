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

# Include all the folders that contain code
include_directories(include)
include_directories(src)
include_directories(src/io)
include_directories(src/ui)
include_directories(src/pathtracing)
include_directories(src/pathtracing/raytracing)
include_directories(src/pathtracing/scene)
include_directories(src/pathtracing/scene/geometry)

find_package(OpenGL)

set(CPP_SOURCES
	# Root folder
    ${CMAKE_CURRENT_SOURCE_DIR}/src/globals.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app.cpp

	# UI folder
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/ui.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/ui.cpp

	# IO folder
	${CMAKE_CURRENT_SOURCE_DIR}/src/io/tiny_obj_loader.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/io/picojson.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/io/sceneLoader.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/io/sceneLoader.cpp
)

set(CUDA_SOURCES
	# src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cu

	# src/pathtracing
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/pathtracer.cuh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/pathtracer.cu

	# src/pathtracing/raytracing
	${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/raytracing/ray.cuh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/raytracing/ray.cu
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/raytracing/intersection.cuh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/raytracing/intersection.cu

	# src/pathtracing/scene
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/scene/camera.cuh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/scene/camera.cu
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/scene/scene.cuh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/scene/scene.cu
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/scene/transform.cuh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pathtracing/scene/transform.cu

	# src/pathtracing/scene/geometry
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
