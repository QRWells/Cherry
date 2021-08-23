// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : path_integrator.cc
// Author      : QRWells
// Created at  : 2021/09/11 3:44
// Description :

#include "path_integrator.h"

#include <algorithm>

#include "../common/cast_record.h"
#include "../core/material.h"
#include "../utility/random.h"

namespace cherry {
using namespace math;

Point3 PathIntegrator::Li(Ray const& ray, std::shared_ptr<Scene> const& scene) {
  Vector3d color(0.0);
  Vector3d it(1.0);
  Ray recursive_ray = ray;
  for (auto depth = 0;; ++depth) {
    Intersection obj_inter;
    if (!scene->Intersect(recursive_ray, obj_inter)) break;

    // intersect with light

    if (obj_inter.material->HasEmission())
      color += obj_inter.material->GetEmission() * it;

    // direct lighting

    Intersection light_inter;
    double pdf_emit;

    scene->SampleLight(light_inter, pdf_emit);
    auto& n = obj_inter.normal;
    auto& nn = light_inter.normal;
    auto& wo = recursive_ray.direction;

    auto obj_to_light = light_inter.coordinate - obj_inter.coordinate;
    auto ws = obj_to_light.Normalized();
    auto dist = obj_to_light.Norm2();

    Ray obj_to_light_ray(obj_inter.coordinate, ws);

    if (Intersection inter;
        scene->Intersect(obj_to_light_ray, inter) &&
        (inter.coordinate - light_inter.coordinate).Norm() < 1e-2) {
      auto fac = std::abs(n.Dot(ws) * nn.Dot(-ws));
      color += light_inter.material->GetEmission() * it *
               obj_inter.material->Evaluate(wo, ws, n) * fac /
               (dist * pdf_emit);
    }

    if (depth > 3) {
      auto russian_roulette = std::min(it.x, 0.9);
      if (auto rr = GetRandomDouble(); rr > russian_roulette) break;
      it /= russian_roulette;
    }

    // indirect lighting for next iteration

    auto wi = obj_inter.material->Sample(wo, n).Normalized();

    Ray next_ray(obj_inter.coordinate, wi);

    if (Intersection next_inter; scene->Intersect(next_ray, next_inter) &&
                                 !next_inter.material->HasEmission()) {
      auto next_pdf = next_inter.material->Pdf(wo, wi, n);
      it *= obj_inter.material->Evaluate(wo, wi, n) * std::abs(wi.Dot(n)) /
            next_pdf;
    }

    recursive_ray = next_ray;
  }
  color.Formalize();
  return color;
}
}  // namespace cherry
