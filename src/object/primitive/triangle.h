// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : triangle.h
// Author      : QRWells
// Created at  : 2021/09/02 2:48
// Description :

#ifndef CHERRY_OBJECT_PRIMITIVE_TRIANGLE
#define CHERRY_OBJECT_PRIMITIVE_TRIANGLE

#include <utility>

#include "../../core/object.h"

namespace cherry {
class Triangle final : public Object {
 public:
  Triangle(const math::Point3& v0, const math::Point3& v1,
           const math::Point3& v2, std::shared_ptr<Material> material)
      : v0_(v0),
        v1_(v1),
        v2_(v2),
        e1_(v1 - v0),
        e2_(v2 - v0),
        material_(std::move(material)) {
    normal_ = e1_.Cross(e2_).Normalized();
  }

  auto Intersect(const Ray &ray, Intersection &intersection) const
      -> bool override;
  auto GetBounds() -> Box override;
  void Sample(Intersection &intersection, double &pdf) override;
  [[nodiscard]] auto HasEmission() const -> bool override;
  [[nodiscard]] auto GetSurfaceArea() const -> double override;

 private:
  math::Point3 v0_, v1_, v2_;
  math::Point3 e1_, e2_;
  math::Vector3d normal_;
  std::shared_ptr<Material> material_ = nullptr;
};
}  // namespace cherry

#endif  // !CHERRY_OBJECT_PRIMITIVE_TRIANGLE
