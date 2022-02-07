// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : sphere.cpp
// Author      : QRWells
// Created at  : 2021/08/26 18:46
// Description :

#include "sphere.h"

#include "../../core/material.h"
#include "../../utility/algorithm.h"
#include "../../utility/constant.h"
#include "../../utility/random.h"

namespace cherry {
auto Sphere::Intersect(const Ray& ray, Intersection& intersection) const
    -> bool {
  auto const kL = ray.origin - center_;
  auto const kA = ray.direction.Norm2();
  auto const kB = 2 * ray.direction.Dot(kL);
  auto const kC = kL.Norm2() - radius2_;
  double t0 = 0;
  double t1 = 0;
  if (!SolveQuadratic(kA, kB, kC, t0, t1)) return false;
  if (t0 < 1e-2) t0 = t1;
  if (t0 < 1e-1) return false;

  Intersection result;
  result.coordinate = math::Vector3d(ray.origin + ray.direction * t0);
  result.normal = math::Vector3d(result.coordinate - center_).Normalized();
  result.material = this->material_;
  result.distance = t0;
  intersection = result;
  return true;
}
auto Sphere::GetBounds() -> Box {
  auto const kR = math::Vector3d(radius_);
  return {center_ - kR, center_ + kR};
}
void Sphere::Sample(Intersection& pos, double& pdf) {
  double const kTheta = PI_TIMES_2 * GetRandomDouble();
  double const kPhi = PI * GetRandomDouble();
  math::Vector3d const kDir(std::cos(kPhi), std::sin(kPhi) * std::cos(kTheta),
                            std::sin(kPhi) * std::sin(kTheta));
  pos.coordinate = center_ + radius_ * kDir;
  pos.normal = kDir;
  pos.material = material_;
  pdf = 1.0 / GetSurfaceArea();
}
auto Sphere::HasEmission() const -> bool {
  return material_->GetEmission().Norm2() > EPSILON;
}
auto Sphere::GetSurfaceArea() const -> double { return radius2_ * PI_TIMES_4; }
}  // namespace cherry
