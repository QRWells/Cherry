// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : plane.cc
// Author      : QRWells
// Created at  : 2021/08/31 17:38
// Description :

#include "plane.h"

#include "../../utility/constant.h"
#include "../../utility/random.h"

namespace cherry {
bool Plane::Intersect(Ray const& ray, Intersection& intersection) const {
  if (ray.direction.Dot(normal_) > 0) return false;
  auto const kT =
      normal_.Dot(position_ - ray.origin) / normal_.Dot(ray.direction);
  if (kT < 0) return false;
  if (e1_.Norm2() > kEpsilon && e2_.Norm2() > kEpsilon) {
    auto const kP = ray(kT);
    auto const kE = kP - position_;
    auto const kT1 = kE.Dot(e1_) / e1_.Norm2();
    auto const kT2 = kE.Dot(e2_) / e2_.Norm2();
    if (kT1 < 0.0 || kT1 > 1.0 || kT2 < 0.0 || kT2 > 1.0) return false;
  }
  intersection.coordinate = ray(kT);
  intersection.material = material_;
  intersection.distance = kT;
  intersection.normal = normal_;
  return true;
}
Box Plane::GetBounds() { return {position_, position_ + e1_ + e2_}; }
void Plane::Sample(Intersection& intersection, double& pdf) {
  if (e1_.Norm2() < kEpsilon || e2_.Norm2() < kEpsilon) [[unlikely]] {
  } else [[likely]] {
    auto const kR1 = GetRandomDouble();
    auto const kR2 = GetRandomDouble();
    intersection.coordinate = position_ + e1_ * kR1 + e2_ * kR2;
    intersection.material = material_;
    intersection.normal = normal_;
    pdf = 1.0 / GetSurfaceArea();
  }
}
bool Plane::HasEmission() const {
  return material_->GetEmission().Norm2() > kEpsilon;
}
double Plane::GetSurfaceArea() const {
  if (e1_.Norm2() < kEpsilon || e2_.Norm2() < kEpsilon) [[unlikely]] {
    return std::numeric_limits<double>::max();
  }
  return e1_.Norm() * e2_.Norm();
}
}  // namespace cherry
