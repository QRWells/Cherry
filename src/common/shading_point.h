// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
// 
// This file is part of Project Cherry.
// File Name   : shading_point.h
// Author      : QRWells
// Created at  : 2021/09/14 14:42
// Description :

#ifndef CHERRY_COMMON_SHADING_POINT
#define CHERRY_COMMON_SHADING_POINT

#include "../math/vector.h"
#include "../utility/algorithm.h"

namespace cherry {
struct ShadingPoint {
  ShadingPoint() = default;
  explicit ShadingPoint(math::Vector3d const& n) : normal(n) {
    GenerateOrthonormalBasis(n, tangent_x, tangent_y);
  }
  explicit ShadingPoint(math::Vector3d const& n, math::Vector3d const& t_x,
                        math::Vector3d const& t_y)
      : normal(n), tangent_x(t_x), tangent_y(t_y) {}

  math::Vector3d normal;
  math::Vector3d tangent_x;
  math::Vector3d tangent_y;

  [[nodiscard]] math::Vector3d ToLocal(math::Vector3d const&) const;
  [[nodiscard]] math::Vector3d ToWorld(math::Vector3d const&) const;
};
}  // namespace cherry

#endif  // !CHERRY_COMMON_SHADING_POINT
