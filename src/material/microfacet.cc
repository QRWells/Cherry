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
  auto const kV = (-wi).Normalized();
  auto const kL = wo.Normalized();

  auto const kDotNl = n.Dot(kL);
  auto const kDotNv = n.Dot(kV);
  if (kDotNl <= 0.0 || kDotNv <= 0.0) return Color(0.0);

  auto const kH_ = kV + kL;
  if (kH_.Norm2() <= EPSILON) return Color(0.0);
  auto const kH = kH_.Normalized();

  auto const kF0 = Interp(F0, this->kd, metallic_);
  auto const kAlpha = roughness_ * roughness_;
  auto const k_ = std::pow(roughness_ + 1.0, 2.0) / 8.0;

  auto const kDotHv = std::clamp(kH.Dot(kV), 0.0, 1.0);

  // Fresnel term
  auto const kF = FresnelSchlick(kDotHv, kF0);

  // Geometry(shadowing-masking term) GGX
  auto const kG = GeometrySmith(n, kV, kL, k_);

  // Distribution of normals GGX
  auto const kD = DistributionGGXTR(n, kH, kAlpha);

  auto const kDenom = 4.0 * kDotNl * kDotNv;
  if (kDenom <= EPSILON) return Color(0.0);

  auto const kSpecular = (kF * kG * kD) / kDenom;
  auto const kd_factor = (Vector3d(1.0) - kF) * (1.0 - metallic_);
  auto const kDiffuse = kd_factor * this->kd * PI_INV;
  return kSpecular + kDiffuse;
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
