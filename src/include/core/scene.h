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

  double emit_area_sum;
  const std::shared_ptr<Camera> camera;

 private:
  // hittable objects
  std::vector<std::shared_ptr<Object>> objects_;
  // emitting objects including light(non-hittable) and hittable objects
  std::vector<std::shared_ptr<Object>> lights_;
  // the bvh tree for acceleration
  Bvh bvh_;

 public:
  [[nodiscard]] auto GetObjects() const
      -> const std::vector<std::shared_ptr<Object>>&;
  [[nodiscard]] auto GetLights() const
      -> const std::vector<std::shared_ptr<Object>>&;
  void SampleLight(Intersection&, double&) const;
  void Add(const std::shared_ptr<Object>& object);
  auto Intersect(const Ray& ray, Intersection& intersection) const -> bool;
  void BuildBvh();
};
}  // namespace cherry

#endif  // !SCENE
