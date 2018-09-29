cmake_minimum_required(VERSION 3.10.3)
project(pathtracer CXX CUDA)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CUDA_NVCC_FLAGS 
    ${CUDA_NVCC_FLAGS}; 
    -dc arch=sm_60)

include_directories(include)

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/app.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/ui.cpp
)

set(CUDA_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cu
    ${CMAKE_CURRENT_SOURCE_DIR}/pathtracing/pathtracer.cu
    ${CMAKE_CURRENT_SOURCE_DIR}/pathtracing/raytracing/ray.cu
    ${CMAKE_CURRENT_SOURCE_DIR}/pathtracing/raytracing/intersection.cu
    ${CMAKE_CURRENT_SOURCE_DIR}/pathtracing/scene/camera.cu   
    ${CMAKE_CURRENT_SOURCE_DIR}/pathtracing/scene/scene.cu
    ${CMAKE_CURRENT_SOURCE_DIR}/pathtracing/scene/transform.cu
    ${CMAKE_CURRENT_SOURCE_DIR}/pathtracing/scene/geometry/shape.cu
    ${CMAKE_CURRENT_SOURCE_DIR}/pathtracing/scene/geometry/sphere.cu
)

add_executable(pathtracer
    ${CUDA_SOURCES}
    ${CPP_SOURCES}
)

get_property(core_options TARGET Qt5::Core PROPERTY INTERFACE_COMPILE_OPTIONS)
string(REPLACE "-fPIC" "" new_core_options ${core_options})
set_property(TARGET Qt5::Core PROPERTY INTERFACE_COMPILE_OPTIONS ${new_core_options})
set_property(TARGET Qt5::Core PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE "ON")

set_source_files_properties(${CUDA_SOURCES} PROPERTIES COMPILE_FLAGS " -Xcompiler=-fPIC")
set_source_files_properties(${CPP_SOURCES} PROPERTIES COMPILE_FLAGS " -fPIC")

target_link_libraries(pathtracer Qt5::Widgets)
