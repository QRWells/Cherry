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
  auto const kIndex = GetRandomUInt(lights_.size() - 1);
  lights_[kIndex]->Sample(intersection, pdf);
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
