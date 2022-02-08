// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : material.cc
// Author      : QRWells
// Created at  : 2021/08/24 5:31
// Description :

#include "core/material.h"

namespace cherry {
auto Material::ToWorld(const math::Vector3d& a, const math::Vector3d& n)
    -> math::Vector3d {
  math::Vector3d c;
  if (std::fabs(n.x) > std::fabs(n.y)) {
    auto const kInvLen = 1.0 / std::sqrt(n.x * n.x + n.z * n.z);
    c = math::Vector3d(n.z * kInvLen, 0.0, -n.x * kInvLen);
  } else {
    auto const kInvLen = 1.0 / std::sqrt(n.y * n.y + n.z * n.z);
    c = math::Vector3d(0.0, n.z * kInvLen, -n.y * kInvLen);
  }
  math::Vector3d const kB = c.Cross(n);
  return a.x * kB + a.y * c + a.z * n;
}
}  // namespace cherry
