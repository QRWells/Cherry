// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : scene.h
// Author      : QRWells
// Created at  : 2021/08/23 20:24
// Description :

#ifndef CHERRY_CORE_SCENE
#define CHERRY_CORE_SCENE
#include <vector>

#include "../acceleration/bvh.h"
#include "camera.h"
#include "light.h"
#include "object.h"

namespace cherry {

class Scene {
 public:
  explicit Scene(const std::shared_ptr<Camera>& camera);

  double emit_area_sum_;
  const std::shared_ptr<Camera> camera_;

 private:
  // hittable objects
  std::vector<std::shared_ptr<Object>> objects_;
  // emitting objects including light(non-hittable) and hittable objects
  std::vector<std::shared_ptr<Object>> lights_;
  // the bvh tree for acceleration
  Bvh bvh_;

 public:
  [[nodiscard]] const std::vector<std::shared_ptr<Object>>& GetObjects() const;
  [[nodiscard]] const std::vector<std::shared_ptr<Object>>& GetLights() const;
  void SampleLight(Intersection&, double&) const;
  void Add(const std::shared_ptr<Object>& object);
  bool Intersect(const Ray& ray, Intersection& intersection) const;
  void BuildBvh();
};
}  // namespace cherry

#endif  // !SCENE
