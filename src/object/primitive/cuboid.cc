// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : cuboid.cc
// Author      : QRWells
// Created at  : 2021/08/31 22:49
// Description :

#include "object/primitive/cuboid.h"

#include "utility/constant.h"
#include "utility/random.h"

namespace cherry {
auto Cuboid::Intersect(Ray const& ray, Intersection& intersection) const
    -> bool {
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
auto Cuboid::GetBounds() -> Box { return {min_, max_}; }
void Cuboid::Sample(Intersection& intersection, double& pdf) {
  auto const d = max_ - min_;
  auto const area_yz = d.y * d.z;
  auto const area_xz = d.x * d.z;
  auto const area_xy = d.x * d.y;
  auto const total_area = 2.0 * (area_xy + area_xz + area_yz);
  if (total_area <= EPSILON) [[unlikely]] {
    pdf = 0.0;
    return;
  }

  auto const r = GetRandomDouble() * total_area;
  auto const u = GetRandomDouble();
  auto const v = GetRandomDouble();

  if (r < area_yz) {
    intersection.coordinate = {min_.x, min_.y + u * d.y, min_.z + v * d.z};
    intersection.normal = {-1, 0, 0};
  } else if (r < 2.0 * area_yz) {
    intersection.coordinate = {max_.x, min_.y + u * d.y, min_.z + v * d.z};
    intersection.normal = {1, 0, 0};
  } else if (r < 2.0 * area_yz + area_xz) {
    intersection.coordinate = {min_.x + u * d.x, min_.y, min_.z + v * d.z};
    intersection.normal = {0, -1, 0};
  } else if (r < 2.0 * area_yz + 2.0 * area_xz) {
    intersection.coordinate = {min_.x + u * d.x, max_.y, min_.z + v * d.z};
    intersection.normal = {0, 1, 0};
  } else if (r < 2.0 * area_yz + 2.0 * area_xz + area_xy) {
    intersection.coordinate = {min_.x + u * d.x, min_.y + v * d.y, min_.z};
    intersection.normal = {0, 0, -1};
  } else {
    intersection.coordinate = {min_.x + u * d.x, min_.y + v * d.y, max_.z};
    intersection.normal = {0, 0, 1};
  }

  intersection.material = material_;
  pdf = 1.0 / total_area;
}
auto Cuboid::HasEmission() const -> bool {
  return material_->GetEmission().Norm2() > EPSILON;
}
auto Cuboid::GetSurfaceArea() const -> double { return area_; }
}  // namespace cherry
