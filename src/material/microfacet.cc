// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : microfacet.cc
// Author      : QRWells
// Created at  : 2021/09/02 3:10
// Description :

#include "material/microfacet.h"

#include "core/material.h"
#include "utility/algorithm.h"
#include "utility/constant.h"
#include "utility/random.h"

using namespace cherry::math;

namespace cherry {
auto MicrofacetMaterial::Evaluate(Vector3d const& wi, Vector3d const& wo,
                                  Vector3d const& n) -> Color {
  auto const kV = -wi.Normalized();
  const auto& k_l = wo;
  auto const kH = (kV + k_l).Normalized();

  auto const kF0 = Interp(F0, kd, metallic_);
  auto const kAlpha = roughness_ * roughness_;
  auto const k_ = std::pow(roughness_ + 1, 2.0) / 8.0;

  auto const kDotNl = std::max(n.Dot(k_l), 0.0);
  auto const kDotNv = std::max(n.Dot(kV), 0.0);
  auto const kDotHv = std::clamp(kH.Dot(kV), 0.0, 1.0);

  // Fresnel term
  auto const kF = FresnelSchlick(kDotHv, kF0);

  // Geometry(shadowing-masking term) GGX
  auto const kG = GeometrySmith(n, kV, k_l, k_);

  // Distribution of normals GGX
  auto const kD = DistributionGGXTR(n, kH, kAlpha);

  auto const kNom = kF * kG * kD;
  auto const kDenom = 1.0 / (kDotNl * kDotNv * 4.0 + 1e-2);

  auto const kSpecular = kNom * kDenom;
  auto kd = Vector3d(1.0) - kF;
  kd *= 1.0 - metallic_;

  auto const kRes = kSpecular + kd * kd * PI_INV;
  return kRes;
}

auto MicrofacetMaterial::Sample(Vector3d const& wi, Vector3d const& n)
    -> Color {
  // TODO(qrwells): new sample method

  auto const kX1 = GetRandomDouble();
  auto const kX2 = GetRandomDouble();
  auto const kZ = std::fabs(1.0 - 2.0 * kX1);
  auto const kR = std::sqrt(1.0 - kZ * kZ);
  auto const kPhi = PI_TIMES_2 * kX2;
  Vector3d const kLocalRay(kR * std::cos(kPhi), kR * std::sin(kPhi), kZ);
  return ToWorld(kLocalRay, n);
}

auto MicrofacetMaterial::Pdf(Vector3d const& wi, Vector3d const& wo,
                             Vector3d const& n) -> double {
  return wo.Dot(n) > 0.0 ? PI_TIMES_2_INV : 0.0;
}
}  // namespace cherry
