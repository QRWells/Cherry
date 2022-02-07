// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : dielectric.cc
// Author      : QRWells
// Created at  : 2021/09/09 7:24
// Description :

#include <algorithm>

#include "dielectric.h"

#include "../utility/algorithm.h"
#include "../utility/random.h"

using namespace cherry::math;

namespace cherry {
auto DielectricMaterial::Evaluate(Vector3d const& wi, Vector3d const& wo,
                                  Vector3d const& n) -> Color {
  auto eta = wi.Dot(n) < 0 ? 1.0 / ior : ior;
  eta = std::clamp(eta, 0.0, 1.0);
  if (auto const kF = Fresnel(wi.Normalized(), n, 1.0, ior);
      GetRandomDouble() > kF)
    return Color(std::pow(eta, 2));
  return kd;
}

auto DielectricMaterial::Sample(Vector3d const& wi, Vector3d const& n)
    -> Vector3d {
  if (auto const kF = Fresnel(wi.Normalized(), n, 1.0, ior);
      GetRandomDouble() > kF)
    return Refract(wi.Normalized(), n, 1.0, ior);
  return Reflect(wi.Normalized(), n);
}

auto DielectricMaterial::Pdf(Vector3d const& wi, Vector3d const& wo,
                             Vector3d const& n) -> double {
  return 1;
}

}  // namespace cherry
