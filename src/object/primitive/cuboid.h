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

#include "../../core/material.h"
#include "../../core/object.h"
#include "../../math/vector.h"

namespace cherry {
class Cuboid final : public Object {
 public:
  Cuboid(math::Vector3d const &center, double const &width,
         double const &height, double const &depth,
         const std::shared_ptr<Material> &mt)
      : area_(8 * (width * height + width * depth + height * depth)),
        material_(mt) {
    min_ = {center.x - width / 2, center.y - height / 2, center.z - depth / 2};
    max_ = {center.x + width / 2, center.y + height / 2, center.z + depth / 2};
  }

  Cuboid(const math::Vector3d &min, const math::Vector3d &max,
         const std::shared_ptr<Material> &mt)
      : min_(min), max_(max), material_(mt) {
    area_ = Box(min, max).SurfaceArea();
  }

  bool Intersect(const Ray &, Intersection &) const override;
  Box GetBounds() override;
  void Sample(Intersection &, double &) override;
  [[nodiscard]] bool HasEmission() const override;
  [[nodiscard]] double GetSurfaceArea() const override;

 private:
  math::Vector3d min_;
  math::Vector3d max_;
  double area_;
  std::shared_ptr<Material> material_;
};
}  // namespace cherry

#endif  // !CHERRY_OBJECT_PRIMITIVE_CUBOID