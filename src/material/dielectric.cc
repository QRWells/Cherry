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
#include <cmath>

#include "material/dielectric.h"

#include "utility/algorithm.h"
#include "utility/random.h"

using namespace cherry::math;

namespace cherry {
auto DielectricMaterial::Evaluate(Vector3d const& wi, Vector3d const& wo,
                                  Vector3d const& n) -> Color {
  if (wo.Norm2() <= EPSILON) return Color(0.0);
  auto const wi_n = wi.Normalized();
  auto const wo_n = wo.Normalized();

  auto const f = Fresnel(wi_n, n, 1.0, ior);

  auto const reflect_dir = Reflect(wi_n, n).Normalized();
  auto refract_dir = Refract(wi_n, n, 1.0, ior);
  auto const has_refract = refract_dir.Norm2() > EPSILON;
  if (has_refract) refract_dir = refract_dir.Normalized();

  auto const cos_o = std::abs(n.Dot(wo_n));
  if (cos_o <= EPSILON) return Color(0.0);

  constexpr double kMatchEps = 1e-6;
  if (wo_n.Dot(reflect_dir) > 1.0 - kMatchEps) {
    return kd * f / cos_o;
  }
  if (has_refract && wo_n.Dot(refract_dir) > 1.0 - kMatchEps) {
    double eta_i = 1.0;
    double eta_t = ior;
    if (wi_n.Dot(n) > 0.0) std::swap(eta_i, eta_t);
    auto const eta = eta_i / eta_t;
    return ks * (1.0 - f) * (eta * eta) / cos_o;
  }

  return Color(0.0);
}

auto DielectricMaterial::Sample(Vector3d const& wi, Vector3d const& n)
    -> Vector3d {
  auto const wi_n = wi.Normalized();
  auto const f = Fresnel(wi_n, n, 1.0, ior);

  auto const refract_dir = Refract(wi_n, n, 1.0, ior);
  if (refract_dir.Norm2() <= EPSILON) return Reflect(wi_n, n);

  if (GetRandomDouble() < f) return Reflect(wi_n, n);
  return refract_dir;
}

auto DielectricMaterial::Pdf(Vector3d const& wi, Vector3d const& wo,
                             Vector3d const& n) -> double {
  if (wo.Norm2() <= EPSILON) return 0.0;
  auto const wi_n = wi.Normalized();
  auto const wo_n = wo.Normalized();

  auto const reflect_dir = Reflect(wi_n, n).Normalized();
  auto refract_dir = Refract(wi_n, n, 1.0, ior);
  auto const has_refract = refract_dir.Norm2() > EPSILON;
  if (has_refract) refract_dir = refract_dir.Normalized();

  constexpr double kMatchEps = 1e-6;
  if (!has_refract) {
    return wo_n.Dot(reflect_dir) > 1.0 - kMatchEps ? 1.0 : 0.0;
  }

  auto const f = Fresnel(wi_n, n, 1.0, ior);
  if (wo_n.Dot(reflect_dir) > 1.0 - kMatchEps) return f;
  if (wo_n.Dot(refract_dir) > 1.0 - kMatchEps) return 1.0 - f;
  return 0.0;
}

}  // namespace cherry
