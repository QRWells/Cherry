// Cherry.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>

// TODO: 在此处引用程序需要的其他标头。

#include "omp.h"
#include "core/camera.h"
#include "core/ray_tracer.h"
#include "core/scene.h"
#include "integrator/path_integrator.h"
#include "material/dielectric.h"
#include "material/diffuse.h"
#include "material/microfacet.h"
#include "material/reflect.h"
#include "object/primitive/cuboid.h"
#include "object/primitive/sphere.h"
#include "object/primitive/triangle.h"
