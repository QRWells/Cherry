/**
 * @file Cherry.h
 * @author QRWells (qirui.wang@moegi.waseda.jp)
 * @brief Header file for main program
 * @version 0.1
 * @date 2022-02-11
 *
 * @copyright Copyright (c) 2021 QRWells. All rights reserved.
 * Licensed under the MIT license.
 *
 */

#pragma once

#include <iostream>

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
#include "omp.h"
