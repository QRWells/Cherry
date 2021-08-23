// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : scene.cc
// Author      : QRWells
// Created at  : 2021/08/23 20:26
// Description :

#include "scene.h"

#include "../utility/random.h"

namespace cherry {

Scene::Scene(const std::shared_ptr<Camera>& camera)
    : emit_area_sum_(0), camera_(camera) {}
const std::vector<std::shared_ptr<Object>>& Scene::GetObjects() const {
  return objects_;
}

const std::vector<std::shared_ptr<Object>>& Scene::GetLights() const {
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
    emit_area_sum_ += object->GetSurfaceArea();
  }
}

bool Scene::Intersect(const Ray& ray, Intersection& intersection) const {
  return bvh_.Intersect(ray, intersection);
}

void Scene::BuildBvh() { bvh_.Construct(objects_); }

}  // namespace cherry
