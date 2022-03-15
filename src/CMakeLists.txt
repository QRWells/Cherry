cmake_minimum_required (VERSION 3.21)

find_package(OpenMP)
find_package(fmt)
find_package(nlohmann_json CONFIG REQUIRED)

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable (Cherry
    "Cherry.cc"

    "acceleration/bvh.cc"

    "core/ray_tracer.cc"
    "core/rasterizer.cc"
    "core/scene.cc"
    "core/camera.cc"
    "core/material.cc"
    "core/texture.cc"
    "core/light.cc"
    "core/renderer.cc" 

    "common/box.cc"
    "common/shading_point.cc" 

    "math/matrix.cc"
    "math/vector.cc"

    "material/diffuse.cc" 
    "material/microfacet.cc"
    "material/reflect.cc" 
    "material/dielectric.cc"

    "light/plane_light.cc"  
    "light/directional_light.cc" 

#   "object/mesh.cc" 
    "object/primitive/sphere.cc" 
    "object/primitive/plane.cc" 
    "object/primitive/cuboid.cc" 
    "object/primitive/triangle.cc" 

    #   "utility/sampler.cc"
    "utility/render_script/render_script_parser.cc" 

    "integrator/normal_integrator.cc" 
    "integrator/path_integrator.cc"  
)

if(OpenMP_CXX_FOUND)
    target_link_libraries(Cherry PUBLIC OpenMP::OpenMP_CXX)
endif()

target_link_libraries(Cherry PUBLIC fmt::fmt)
target_link_libraries(Cherry PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
