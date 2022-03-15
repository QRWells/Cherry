// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : cuboid.h
// Author      : QRWells
// Created at  : 2021/08/31 22:49
// Description :

#ifndef CHERRY_OBJECT_PRIMITIVE_CUBOID
#define CHERRY_OBJECT_PRIMITIVE_CUBOID

#include <utility>

#include "core/material.h"
#include "core/object.h"
#include "math/vector.h"

namespace cherry {
class Cuboid final : public Object {
 public:
  Cuboid(math::Vector3d const &center, double const &width,
         double const &height, double const &depth,
         std::shared_ptr<Material> mt)
      : area_(8 * (width * height + width * depth + height * depth)),
        material_(std::move(mt)) {
    min_ = {center.x - width / 2, center.y - height / 2, center.z - depth / 2};
    max_ = {center.x + width / 2, center.y + height / 2, center.z + depth / 2};
  }

  Cuboid(const math::Vector3d &min, const math::Vector3d &max,
         std::shared_ptr<Material> mt)
      : min_(min), max_(max), material_(std::move(mt)) {
    area_ = Box(min, max).SurfaceArea();
  }

  auto Intersect(const Ray &ray, Intersection &intersection) const
      -> bool override;
  auto GetBounds() -> Box override;
  void Sample(Intersection &intersection, double &pdf) override;
  [[nodiscard]] auto HasEmission() const -> bool override;
  [[nodiscard]] auto GetSurfaceArea() const -> double override;

 private:
  math::Vector3d min_;
  math::Vector3d max_;
  double area_;
  std::shared_ptr<Material> material_;
};
}  // namespace cherry

#endif  // !CHERRY_OBJECT_PRIMITIVE_CUBOID