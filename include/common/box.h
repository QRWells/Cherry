// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : box.h
// Author      : QRWells
// Created at  : 2021/08/24 15:10
// Description :

#ifndef CHERRY_COMMON_BOX
#define CHERRY_COMMON_BOX

#include "common/intersection.h"
#include "common/ray.h"
#include "math/vector.h"

namespace cherry {
struct Box {
 public:
  Box() = default;
  explicit Box(math::Point3 const& p) : min(p), max(p) {}
  Box(math::Point3 const& min, math::Point3 const& max) : min(min), max(max) {}

  math::Point3 min;
  math::Point3 max;

  [[nodiscard]] auto Centroid() const -> math::Vector3d {
    return 0.5 * min + 0.5 * max;
  }
  [[nodiscard]] auto Diagonal() const -> math::Vector3d { return max - min; }
  [[nodiscard]] auto SurfaceArea() const -> double {
    auto const kDiagonal = Diagonal();
    return 2 * (kDiagonal.x * kDiagonal.y + kDiagonal.x * kDiagonal.z +
                kDiagonal.y * kDiagonal.z);
  }
  [[nodiscard]] auto MaxExtent() const -> int;
  [[nodiscard]] auto Offset(math::Point3 const& p) const -> math::Vector3d;
  [[nodiscard]] auto Intersect(Ray const&, Intersection&) const -> bool;
  [[nodiscard]] auto Union(Box const&) const -> Box;
  [[nodiscard]] auto Overlaps(Box const&) const -> bool;
  [[nodiscard]] auto Inside(math::Point3 const&) const -> bool;
};
}  // namespace cherry

#endif  // !CHERRY_COMMON_BOX
