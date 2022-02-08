// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : diffuse.cc
// Author      : QRWells
// Created at  : 2021/08/26 2:43
// Description :

#include "material/diffuse.h"

#include "utility/constant.h"
#include "utility/random.h"

namespace cherry {

auto DiffuseMaterial::Evaluate(const math::Vector3d& wi,
                               const math::Vector3d& wo,
                               const math::Vector3d& n) -> math::Color {
  return n.Dot(wo) > 0.0 ? kd * PI_INV : math::Color(0.0);
}
auto DiffuseMaterial::Sample(const math::Vector3d& wi, const math::Vector3d& n)
    -> math::Vector3d {
  double const kX1 = GetRandomDouble();
  double const kX2 = GetRandomDouble();
  double const kZ = std::fabs(1.0 - 2.0 * kX1);
  double const kR = std::sqrt(1.0 - kZ * kZ);
  double const kPhi = 2 * PI * kX2;
  math::Vector3d const kLocalRay(kR * std::cos(kPhi), kR * std::sin(kPhi), kZ);
  return ToWorld(kLocalRay, n);
}
auto DiffuseMaterial::Pdf(const math::Vector3d& wi, const math::Vector3d& wo,
                          const math::Vector3d& n) -> double {
  return wo.Dot(n) > 0.0 ? PI_TIMES_2_INV : 0.0;
}

// math::Color DiffuseMaterial::GetEmission() { return emission_; }
}  // namespace cherry
