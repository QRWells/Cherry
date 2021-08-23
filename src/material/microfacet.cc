// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : microfacet.cc
// Author      : QRWells
// Created at  : 2021/09/02 3:10
// Description :

#include "microfacet.h"

#include "../utility/algorithm.h"
#include "../utility/constant.h"
#include "../utility/random.h"

using namespace cherry::math;

namespace cherry {
Color MicrofacetMaterial::Evaluate(Vector3d const& wi, Vector3d const& wo,
                                   Vector3d const& n) {
  auto const kV = -wi.Normalized();
  auto& kL = wo;
  auto const kH = (kV + kL).Normalized();

  auto const kF0 = Mix(f0_, kd_, metallic_);
  auto const kAlpha = roughness_ * roughness_;
  auto const k = std::pow(roughness_ + 1, 2.0) / 8.0;

  auto const kDotNl = std::max(n.Dot(kL), 0.0);
  auto const kDotNv = std::max(n.Dot(kV), 0.0);
  auto const kDotHv = std::clamp(kH.Dot(kV), 0.0, 1.0);

  // Fresnel term
  auto const kF = FresnelSchlick(kDotHv, kF0);

  // Geometry(shadowing-masking term) GGX
  auto const kG = GeometrySmith(n, kV, kL, k);

  // Distribution of normals GGX
  auto const kD = DistributionGGXTR(n, kH, kAlpha);

  auto const kNom = kF * kG * kD;
  auto const kDenom = 1.0 / (kDotNl * kDotNv * 4.0 + 1e-2);

  auto const kSpecular = kNom * kDenom;
  auto kd = Vector3d(1.0) - kF;
  kd *= 1.0 - metallic_;

  auto const kRes = kSpecular + kd * kd_ * kPiInv;
  return kRes;
}

Color MicrofacetMaterial::Sample(Vector3d const& wi, Vector3d const& n) {
  // TODO: new sample method

  auto const kX1 = GetRandomDouble();
  auto const kX2 = GetRandomDouble();
  auto const kZ = std::fabs(1.0 - 2.0 * kX1);
  auto const kR = std::sqrt(1.0 - kZ * kZ);
  auto const kPhi = k2Pi * kX2;
  Vector3d const kLocalRay(kR * std::cos(kPhi), kR * std::sin(kPhi), kZ);
  return ToWorld(kLocalRay, n);
}

double MicrofacetMaterial::Pdf(Vector3d const& wi, Vector3d const& wo,
                               Vector3d const& n) {
  return wo.Dot(n) > 0.0 ? k2PiInv : 0.0;
}
}  // namespace cherry
