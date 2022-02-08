// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : reflect.cc
// Author      : QRWells
// Created at  : 2021/09/04 5:18
// Description :

#include "material/reflect.h"

#include "utility/algorithm.h"
#include "utility/constant.h"

using namespace cherry::math;

namespace cherry {
auto ReflectMaterial::Evaluate(Vector3d const& wi, Vector3d const& wo,
                               Vector3d const& n) -> Color {
  auto const kD = 1 - Fresnel(wi.Normalized(), n, 1, ior);
  auto const kS = CookTorrance(wi, wo, n, 2, 1, ior);
  return n.Dot(wo) > 0.0 ? ks * kS + kD * kd * PI_INV : Color(0.0);
}

auto ReflectMaterial::Sample(Vector3d const& wi, Vector3d const& n) -> Color {
  return Reflect(wi.Normalized(), n);
}
auto ReflectMaterial::Pdf(Vector3d const& wi, Vector3d const& wo,
                          Vector3d const& n) -> double {
  return 1;
}
}  // namespace cherry
