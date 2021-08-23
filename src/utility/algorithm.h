// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : algorithm.h
// Author      : QRWells
// Created at  : 2021/08/26 19:00
// Description :

#ifndef CHERRY_UTILITY_ALGORITHM
#define CHERRY_UTILITY_ALGORITHM

#include <algorithm>
#include <cmath>

#include "../math/vector.h"
#include "constant.h"

namespace cherry {

inline double DegToRad(double const& deg) { return deg * kPi / 180.0; }
inline math::Vector3d Mix(math::Vector3d const& x, math::Vector3d const& y,
                          double const& level) {
  return x * (1 - level) + y * level;
}
inline bool SolveQuadratic(double const& a, double const& b, double const& c,
                           double& x0, double& x1) {
  if (auto const kDiscriminant = b * b - 4 * a * c; kDiscriminant < 0)
    return false;
  else if (fabs(kDiscriminant) < kEpsilon)
    x0 = x1 = -0.5 * b / a;
  else {
    auto const kQ = b > 0 ? -0.5 * (b + sqrt(kDiscriminant))
                          : -0.5 * (b - sqrt(kDiscriminant));
    x0 = kQ / a;
    x1 = c / kQ;
  }
  if (x0 > x1) std::swap(x0, x1);
  return true;
}

inline double DistributionGGXTR(math::Vector3d const& n,
                                math::Vector3d const& h, double const& a) {
  auto const&& kA2 = a * a;
  auto const kNDotH = std::max(n.Dot(h), 0.0);
  auto const kNDotH2 = kNDotH * kNDotH;

  auto denominator = kNDotH2 * (kA2 - 1.0) + 1.0;
  denominator = kPi * denominator * denominator;

  return kA2 / denominator;
}

inline math::Vector3d FresnelSchlick(double const& cos_theta,
                                     math::Vector3d const& f0) {
  return f0 + (math::Vector3d(1.0) - f0) *
                  std::pow(std::clamp(1.0 - cos_theta, 0.0, 1.0), 5.0);
}

inline double GeometrySchlickGGX(double const& n_dot_v, double const& k) {
  auto const& kNom = n_dot_v;
  auto const kDenominator = n_dot_v * (1.0 - k) + k;

  return kNom / kDenominator;
}

inline double GeometrySmith(math::Vector3d const& n, math::Vector3d const& v,
                            math::Vector3d const& l, double const& k) {
  auto const kNDotV = std::max(n.Dot(v), 0.0);
  auto const kNDotL = std::max(n.Dot(l), 0.0);
  auto const kGgx1 = GeometrySchlickGGX(kNDotV, k);
  auto const kGgx2 = GeometrySchlickGGX(kNDotL, k);

  return kGgx1 * kGgx2;
}

// Compute reflection direction
inline math::Vector3d Reflect(math::Vector3d const& i,
                              math::Vector3d const& n) {
  return i - 2.0 * i.Dot(n) * n;
}

// Compute refraction direction using Snell's law
//
// We need to handle with care the two possible situations:
//
//    - When the ray is inside the object
//
//    - When the ray is outside.
//
// If the ray is outside, you need to make cos(i) positive cos(i) = -n.I
//
// If the ray is inside, you need to invert the refractive indices and negate
// the normal n
inline math::Vector3d Refract(math::Vector3d const& i, math::Vector3d const& n,
                              double const& ior_in, double const& ior_out) {
  auto cos_i = std::clamp(i.Dot(n), -1.0, 1.0);
  auto eta_i = ior_in, eta_t = ior_out;
  math::Vector3d norm = n;
  if (cos_i < 0)
    cos_i = -cos_i;
  else {
    std::swap(eta_i, eta_t);
    norm = -norm;
  }
  auto const kEta = eta_i / eta_t;
  auto const k = 1 - kEta * kEta * (1 - cos_i * cos_i);
  if (k < 0) return math::Vector3d();
  return kEta * i + (kEta * cos_i - sqrt(k)) * norm;
}

/**
 * \brief compute Fresnel equation.
 * As a consequence of the conservation of energy, transmittance is given by:
 * kt = 1 - kr;
 * \param i the incident view direction
 * \param n the normal at the intersection point
 * \param in_ior the refractive index of the material the ray refract from.
 * \param out_ior the refractive index of the material the ray refract into.
 * \return kr the Fresnel component
 */
inline double Fresnel(math::Vector3d const& i, math::Vector3d const& n,
                      double const& in_ior, double const& out_ior) {
  auto cos_i = std::clamp(i.Dot(n), -1.0, 1.0);
  auto eta_i(in_ior);
  auto eta_t(out_ior);
  if (cos_i > 0) std::swap(eta_i, eta_t);
  // Total internal reflection
  if (auto const kSinT =
          eta_i / eta_t * std::sqrt(std::max(0.0, 1 - cos_i * cos_i));
      kSinT >= 1)
    return 1;
  else [[likely]] {
    double const kCosT = sqrt(std::max(0.0, 1 - kSinT * kSinT));
    cos_i = std::fabs(cos_i);
    double const kRs =
        (eta_t * cos_i - eta_i * kCosT) / (eta_t * cos_i + eta_i * kCosT);
    double const kRp =
        (eta_i * cos_i - eta_t * kCosT) / (eta_i * cos_i + eta_t * kCosT);
    return (kRs * kRs + kRp * kRp) / 2;
  }
}

inline math::Vector3d CookTorrance(math::Vector3d const& wi,
                                   math::Vector3d const& wo,
                                   math::Vector3d const& n,
                                   double const& roughness,
                                   math::Vector3d const& f0) {
  auto const kV = -wi;
  auto& kL = wo;
  auto const kH = (kV + kL).Normalized();

  auto const kDotNl = n.Dot(kL);
  auto const kDotNv = n.Dot(kV);
  auto const kDotHv = kH.Dot(kV);

  // Fresnel term
  auto const kF = FresnelSchlick(kDotHv, f0);

  // Geometry(shadowing-masking term) GGX
  auto const k = std::pow(roughness + 1.0, 2.0) * 0.125;
  auto const kG = GeometrySmith(n, kV, kL, k);

  // Distribution of normals GGX
  auto const kAlpha = std::pow(roughness, 2.0);
  auto const kD = DistributionGGXTR(n, kH, kAlpha);

  auto const&& kResult = kF * kG * kD / (kDotNl * kDotNv * 4.0);
  return kResult;
}

inline double CookTorrance(math::Vector3d const& wi, math::Vector3d const& wo,
                           math::Vector3d const& n, double const& roughness,
                           double const& in_ior, double const& out_ior) {
  auto const kV = -wi.Normalized();
  auto& kL = wo;
  auto const kH = (kV + kL).Normalized();

  auto const kDotNl = n.Dot(kL);
  auto const kDotNv = n.Dot(kV);

  // Fresnel term
  auto const kF = Fresnel(wi, n, in_ior, out_ior);

  // Geometry(shadowing-masking term) GGX
  auto const k = std::pow(roughness + 1.0, 2.0) * 0.125;
  auto const kG = GeometrySmith(n, kV, kL, k);

  // Distribution of normals GGX
  auto const kAlpha = std::pow(roughness, 2.0);
  auto const kD = DistributionGGXTR(n, kH, kAlpha);

  auto const&& kResult = kF * kG * kD / (kDotNl * kDotNv * 4.0);
  return kResult;
}

inline void GenerateOrthonormalBasis(math::Vector3d const& n,
                                     math::Vector3d& t_x, math::Vector3d& t_y) {
  if (std::abs(n.x) > std::abs(n.y)) {
    auto const kInvNorm = 1.0 / std::sqrt(n.x * n.x + n.z * n.z);
    t_y = math::Vector3d(n.z * kInvNorm, 0, -n.x * kInvNorm);
  } else {
    auto const kInvNorm = 1.0 / std::sqrt(n.y * n.y + n.z * n.z);
    t_y = math::Vector3d(0, n.z * kInvNorm, -n.y * kInvNorm);
  }
  t_x = t_y.Cross(n).Normalized();
}
}  // namespace cherry

#endif  // !CHERRY_UTILITY_ALGORITHM
