// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : ray.h
// Author      : QRWells
// Created at  : 2021/08/23 22:07
// Description :

#ifndef CHERRY_COMMON_RAY
#define CHERRY_COMMON_RAY

#include "../math/vector.h"

namespace cherry {
struct Ray {
  math::Point3 origin;
  math::Vector3d direction;
  math::Vector3d direction_inv;

  Ray() = default;

  explicit Ray(math::Point3 const& dir) : direction(dir) {
    direction_inv = 1 / direction;
  }
  Ray(math::Point3 const& origin, math::Vector3d const& dir)
      : origin(origin), direction(dir) {
    direction_inv = 1 / direction;
  }

  auto operator()(double const& t) const -> math::Point3 {
    return origin + direction * t;
  }
};

}  // namespace cherry
#endif  // !CHERRY_COMMON_RAY
