// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : shading_point.cc
// Author      : QRWells
// Created at  : 2021/09/14 14:43
// Description :

#include "common/shading_point.h"

namespace cherry {
auto ShadingPoint::ToLocal(math::Vector3d const& v) const -> math::Vector3d {
  return {v.Dot(tangent_x), v.Dot(tangent_y), v.Dot(normal)};
}
auto ShadingPoint::ToWorld(math::Vector3d const& v) const -> math::Vector3d {
  return tangent_x * v.x + tangent_y * v.y + normal * v.z;
}
}  // namespace cherry
