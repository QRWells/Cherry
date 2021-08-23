// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : cuboid.cc
// Author      : QRWells
// Created at  : 2021/08/31 22:49
// Description :

#include "cuboid.h"

#include "../../utility/constant.h"
#include "../../utility/random.h"

namespace cherry {
bool Cuboid::Intersect(Ray const& ray, Intersection& intersection) const {
  Intersection result;

  auto const kTMin = (min_ - ray.origin) * ray.direction_inv;
  auto const kTMax = (max_ - ray.origin) * ray.direction_inv;

  auto t0 = Min(kTMin, kTMax);
  auto t1 = Max(kTMin, kTMax);

  auto const kTEnter = std::max({t0.x, t0.y, t0.z});

  if (auto const kTExit = std::min({t1.x, t1.y, t1.z});
      (kTEnter >= kTExit) || kTExit < 0)
    return false;
  if (kTEnter < 0.5) return false;

  result.coordinate = ray(kTEnter);
  result.material = this->material_;
  result.distance = kTEnter;

  if (fabs(result.coordinate.x - min_.x) < 1e-2)
    result.normal = {-1, 0, 0};
  else if (fabs(result.coordinate.x - max_.x) < 1e-2)
    result.normal = {1, 0, 0};
  else if (fabs(result.coordinate.y - min_.y) < 1e-2)
    result.normal = {0, -1, 0};
  else if (fabs(result.coordinate.y - max_.y) < 1e-2)
    result.normal = {0, 1, 0};
  else if (fabs(result.coordinate.z - min_.z) < 1e-2)
    result.normal = {0, 0, -1};
  else if (fabs(result.coordinate.z - max_.z) < 1e-2)
    result.normal = {0, 0, 1};
  intersection = result;
  return true;
}
Box Cuboid::GetBounds() { return Box(min_, max_); }
void Cuboid::Sample(Intersection& intersection, double& pdf) {
  auto i = GetRandomDouble(), j = GetRandomDouble();
  int const k = static_cast<int>(GetRandomDouble() * 6);
  math::Vector3d coords;
  switch (k) {
    case 0:
      coords = {0, i, j};
      intersection.normal = {-1, 0, 0};
      break;
    case 1:
      coords = {1, i, j};
      intersection.normal = {1, 0, 0};
      break;
    case 2:
      coords = {i, 0, j};
      intersection.normal = {0, -1, 0};
      break;
    case 3:
      coords = {i, 1, j};
      intersection.normal = {0, 1, 0};
      break;
    case 4:
      coords = {i, j, 0};
      intersection.normal = {0, 0, -1};
      break;
    default:
      coords = {i, j, 1};
      intersection.normal = {0, 0, 1};
      break;
  }
  intersection.coordinate = (max_ - min_) * coords + min_;
  intersection.material = material_;
  pdf = 1.0 / area_;
}
bool Cuboid::HasEmission() const {
  return material_->GetEmission().Norm2() > kEpsilon;
}
double Cuboid::GetSurfaceArea() const { return area_; }
}  // namespace cherry
