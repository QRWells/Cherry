// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : plane.h
// Author      : QRWells
// Created at  : 2021/08/31 17:37
// Description :

#ifndef CHERRY_OBJECT_PRIMITIVE_PLANE
#define CHERRY_OBJECT_PRIMITIVE_PLANE

#include <utility>

#include "../../core/material.h"
#include "../../core/object.h"

namespace cherry {
class Plane final : public Object {
 public:
  Plane(const math::Point3& position, const math::Vector3d& e1,
        const math::Vector3d& e2, std::shared_ptr<Material> material)
      : e1_(e1),
        e2_(e2),
        position_(position),
        normal_(e1.Cross(e2).Normalized()),
        material_(std::move(material)) {}
  Plane(const math::Point3& position, const math::Vector3d& normal,
        std::shared_ptr<Material> material)
      : position_(position), normal_(normal), material_(std::move(material)) {}

  auto Intersect(const Ray& ray, Intersection& intersection) const
      -> bool override;
  auto GetBounds() -> Box override;
  void Sample(Intersection& intersection, double& pdf) override;
  [[nodiscard]] auto HasEmission() const -> bool override;
  [[nodiscard]] auto GetSurfaceArea() const -> double override;

 private:
  math::Vector3d e1_, e2_;
  math::Point3 position_;
  math::Vector3d normal_;
  std::shared_ptr<Material> material_;
};
}  // namespace cherry

#endif  //  !CHERRY_OBJECT_PRIMITIVE_PLANE