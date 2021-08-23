# CMakeList.txt: Cherry 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.9)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

#find_package(Eigen3 CONFIG REQUIRED)

add_executable (Cherry
"Cherry.cc" "Cherry.h"

"acceleration/bvh.h" "acceleration/bvh.cc"
"core/ray_tracer.h" "core/ray_tracer.cc"
"core/integrator.h" "core/integrator.cc"
"core/rasterizer.h" "core/rasterizer.cc"
"core/scene.h" "core/scene.cc"
"core/object.h" "core/object.cc"
"core/camera.h" "core/camera.cc"
"core/material.h" "core/material.cc"
"core/texture.h" "core/texture.cc"
"core/light.h" "core/light.cc" 

"common/box.h" "common/box.cc"
"common/intersection.h" "common/intersection.cc" 
"common/ray.h" "common/ray.cc"
"common/shading_point.h" "common/shading_point.cc" 

"math/matrix.h" "math/matrix.cc" 
"math/vector.h" "math/vector.cc"

"material/diffuse.h" "material/diffuse.cc" 
"material/microfacet.h" "material/microfacet.cc"
"material/reflect.h" "material/reflect.cc" 
"material/dielectric.h" "material/dielectric.cc"

"light/plane_light.h" "light/plane_light.cc"  
"light/directional_light.h" "light/directional_light.cc" 

#"object/mesh.h" "object/mesh.cc" 
"object/primitive/sphere.h" "object/primitive/sphere.cc" 
"object/primitive/plane.h" "object/primitive/plane.cc" 
"object/primitive/cuboid.h" "object/primitive/cuboid.cc" 
"object/primitive/triangle.h" "object/primitive/triangle.cc" 

"utility/constant.h" "utility/constant.cc" 
"utility/random.h" "utility/random.cc" 
"utility/algorithm.h" "utility/algorithm.cc" 

"integrator/path_integrator.h" "integrator/path_integrator.cc" )

if(OpenMP_CXX_FOUND)
    target_link_libraries(Cherry PUBLIC OpenMP::OpenMP_CXX)
endif()

#target_link_libraries(Cherry Eigen3::Eigen)
