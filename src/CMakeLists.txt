cmake_minimum_required (VERSION 3.21)

find_package(OpenMP)
find_package(fmt)

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable (Cherry
"Cherry.cc" "include/Cherry.h"

"include/acceleration/bvh.h"        "acceleration/bvh.cc"

"include/core/ray_tracer.h"         "core/ray_tracer.cc"
"include/core/integrator.h" 
"include/core/rasterizer.h"         "core/rasterizer.cc"
"include/core/scene.h"              "core/scene.cc"
"include/core/object.h" 
"include/core/camera.h"             "core/camera.cc"
"include/core/material.h"           "core/material.cc"
"include/core/texture.h"            "core/texture.cc"
"include/core/light.h"              "core/light.cc"
"include/core/renderer.h"           "core/renderer.cc" 

"include/common/box.h"              "common/box.cc"
"include/common/intersection.h"
"include/common/ray.h"
"include/common/shading_point.h"    "common/shading_point.cc" 

"include/math/matrix.h"             "math/matrix.cc" 
"include/math/vector.h"             "math/vector.cc"

"include/material/diffuse.h"        "material/diffuse.cc" 
"include/material/microfacet.h"     "material/microfacet.cc"
"include/material/reflect.h"        "material/reflect.cc" 
"include/material/dielectric.h"     "material/dielectric.cc"

"include/light/plane_light.h"       "light/plane_light.cc"  
"include/light/directional_light.h" "light/directional_light.cc" 

#"include/object/mesh.h" "object/mesh.cc" 
"include/object/primitive/sphere.h"     "object/primitive/sphere.cc" 
"include/object/primitive/plane.h"      "object/primitive/plane.cc" 
"include/object/primitive/cuboid.h"     "object/primitive/cuboid.cc" 
"include/object/primitive/triangle.h"   "object/primitive/triangle.cc" 

"include/utility/constant.h"
"include/utility/random.h"
"include/utility/algorithm.h"
"include/utility/render_script_parser.h"    "utility/render_script_parser.cc" 

"include/integrator/normal_integrator.h"    "integrator/normal_integrator.cc" 
"include/integrator/path_integrator.h"      "integrator/path_integrator.cc"  
#"include/utility/sampler.h" "utility/sampler.cc"
)

if(OpenMP_CXX_FOUND)
    target_link_libraries(Cherry PUBLIC OpenMP::OpenMP_CXX)
endif()

target_link_libraries(Cherry PUBLIC fmt::fmt)