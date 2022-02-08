// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : sphere.h
// Author      : QRWells
// Created at  : 2021/08/26 18:46
// Description :

#ifndef CHERRY_OBJECT_PRIMITIVE_SPHERE
#define CHERRY_OBJECT_PRIMITIVE_SPHERE
#include <utility>

#include "../../core/object.h"

namespace cherry {
class Sphere final : public Object {
 public:
  Sphere(const math::Point3 &center, const double &r,
         std::shared_ptr<Material> m)
      : material_(std::move(m)), center_(center), radius_(r), radius2_(r * r) {}

  auto Intersect(const Ray &ray, Intersection &intersection) const
      -> bool override;
  auto GetBounds() -> Box override;
  void Sample(Intersection &intersection, double &pdf) override;
  [[nodiscard]] auto HasEmission() const -> bool override;
  [[nodiscard]] auto GetSurfaceArea() const -> double override;

 private:
  std::shared_ptr<Material> material_;
  math::Point3 center_;
  double radius_;
  double radius2_;
};
}  // namespace cherry

#endif  // !CHERRY_OBJECT_PRIMITIVE_SPHERE
