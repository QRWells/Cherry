// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : scene.cc
// Author      : QRWells
// Created at  : 2021/08/23 20:26
// Description :

#include <utility>

#include "core/scene.h"
#include "utility/random.h"

namespace cherry {

Scene::Scene(std::shared_ptr<Camera> camera)
    : emit_area_sum(0), camera(std::move(camera)) {}
auto Scene::GetObjects() const -> const std::vector<std::shared_ptr<Object>>& {
  return objects_;
}

auto Scene::GetLights() const -> const std::vector<std::shared_ptr<Object>>& {
  return lights_;
}

void Scene::SampleLight(Intersection& intersection, double& pdf) const {
  pdf = 0.0;
  if (lights_.empty() || emit_area_sum <= EPSILON) return;

  auto const kR = GetRandomDouble() * emit_area_sum;
  double area_sum = 0.0;
  for (auto const& light : lights_) {
    auto const area = light->GetSurfaceArea();
    area_sum += area;
    if (kR <= area_sum) {
      double pdf_area = 0.0;
      light->Sample(intersection, pdf_area);
      pdf = pdf_area * (area / emit_area_sum);
      return;
    }
  }

  // Fallback to the last light if floating point accumulation misses.
  auto const area = lights_.back()->GetSurfaceArea();
  double pdf_area = 0.0;
  lights_.back()->Sample(intersection, pdf_area);
  pdf = pdf_area * (area / emit_area_sum);
}

void Scene::Add(const std::shared_ptr<Object>& object) {
  objects_.emplace_back(object);
  if (object->HasEmission()) {
    lights_.emplace_back(object);
    emit_area_sum += object->GetSurfaceArea();
  }
}

auto Scene::Intersect(Ray const& ray, Intersection& intersection) const
    -> bool {
  return bvh_.Intersect(ray, intersection);
}

void Scene::BuildBvh() { bvh_.Construct(objects_); }

}  // namespace cherry
