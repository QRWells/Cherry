// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : path_integrator.cc
// Author      : QRWells
// Created at  : 2021/09/11 3:44
// Description :

#include <algorithm>
#include <cmath>

#include "core/material.h"
#include "integrator/path_integrator.h"
#include "utility/random.h"

namespace cherry {
using namespace math;

auto PathIntegrator::Li(Ray const& ray, std::shared_ptr<Scene> const& scene)
    -> Point3 {
  Vector3d color(0.0);
  Vector3d it(1.0);
  Ray recursive_ray = ray;
  for (auto depth = 0;; ++depth) {
    Intersection obj_inter;
    if (!scene->Intersect(recursive_ray, obj_inter)) break;

    // intersect with light

    if (obj_inter.material->HasEmission()) [[unlikely]]
      color += obj_inter.material->GetEmission() * it;

    // direct lighting

    if (!scene->GetLights().empty()) {
      Intersection light_inter;
      double pdf_emit = 0.0;

      scene->SampleLight(light_inter, pdf_emit);
      if (pdf_emit > EPSILON) {
        auto const& n = obj_inter.normal;
        auto const& nn = light_inter.normal;
        auto const& wo = recursive_ray.direction;

        auto const obj_to_light = light_inter.coordinate - obj_inter.coordinate;
        auto const dist2 = obj_to_light.Norm2();
        if (dist2 > EPSILON) {
          auto const ws = obj_to_light.Normalized();
          auto const cos_surface = std::max(0.0, n.Dot(ws));
          auto const cos_light = std::max(0.0, nn.Dot(-ws));
          if (cos_surface > 0.0 && cos_light > 0.0) {
            Ray obj_to_light_ray(obj_inter.coordinate, ws);
            Intersection occ;
            if (scene->Intersect(obj_to_light_ray, occ) &&
                (occ.coordinate - light_inter.coordinate).Norm2() < 1e-4) {
              auto const fac = cos_surface * cos_light;
              color += light_inter.material->GetEmission() * it *
                       obj_inter.material->Evaluate(wo, ws, n) * fac /
                       (dist2 * pdf_emit);
            }
          }
        }
      }
    }

    if (depth > 3) {
      auto russian_roulette = std::min(std::max(it.MaxElement(), 0.0), 0.9);
      if (russian_roulette <= EPSILON) break;
      if (auto rr = GetRandomDouble(); rr > russian_roulette) break;
      it /= russian_roulette;
    }

    // indirect lighting for next iteration

    auto const& wo = recursive_ray.direction;
    auto const& n = obj_inter.normal;
    auto wi = obj_inter.material->Sample(wo, n);
    if (wi.Norm2() <= EPSILON) break;
    wi = wi.Normalized();

    auto const pdf_bsdf = obj_inter.material->Pdf(wo, wi, n);
    if (pdf_bsdf <= EPSILON) break;

    auto const f = obj_inter.material->Evaluate(wo, wi, n);
    it *= f * std::abs(wi.Dot(n)) / pdf_bsdf;

    recursive_ray = Ray(obj_inter.coordinate, wi);
  }
  return color;
}
}  // namespace cherry
