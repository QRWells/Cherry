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

#include "../../core/object.h"

namespace cherry {
class Triangle final : public Object {
 public:
  Triangle(const math::Point3& v0, const math::Point3& v1,
           const math::Point3& v2, const std::shared_ptr<Material>& material)
      : v0_(v0),
        v1_(v1),
        v2_(v2),
        e1_(v1 - v0),
        e2_(v2 - v0),
        material_(material) {
    normal_ = e1_.Cross(e2_).Normalized();
  }

  bool Intersect(const Ray&, Intersection&) const override;
  Box GetBounds() override;
  void Sample(Intersection&, double&) override;
  [[nodiscard]] bool HasEmission() const override;
  [[nodiscard]] double GetSurfaceArea() const override;

 private:
  math::Point3 v0_, v1_, v2_;
  math::Point3 e1_, e2_;
  math::Vector3d normal_;
  std::shared_ptr<Material> material_ = nullptr;
};
}  // namespace cherry

#endif  // !CHERRY_OBJECT_PRIMITIVE_TRIANGLE
