// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : sampler.cc
// Author      : QRWells
// Created at  : 2021/09/25 0:33
// Description :

#include "sampler.h"

#include "constant.h"

namespace cherry {
using namespace math;
auto Sampler::UniformSample1D() const -> double {
  static std::uniform_real_distribution<double> dist(0, 1);
  return dist(rng_);
}

auto Sampler::UniformSample2D() const -> Vector2d {
  return {UniformSample1D(), UniformSample1D()};
}

auto Sampler::UniformSampleHemisphere() const -> Vector3d {
  auto const kDis = UniformSample2D();
  auto const kZ = kDis.x;
  auto const kR = std::sqrt(std::max(0.0, 1 - kZ * kZ));
  auto const kPhi = PI_TIMES_2 * kDis.y;
  return {kR * std::cos(kPhi), kR * std::sin(kPhi), kZ};
}

auto Sampler::UniformHemispherePdf() -> double { return PI_TIMES_2_INV; }

auto Sampler::UniformSampleSphere() const -> Vector3d {
  auto const kDis = UniformSample2D();
  auto const kZ = 1 - 2 * kDis.x;
  auto const kR = std::sqrt(std::max(0.0, 1 - kZ * kZ));
  auto const kPhi = PI_TIMES_2 * kDis.y;
  return {kR * std::cos(kPhi), kR * std::sin(kPhi), kZ};
}

auto Sampler::UniformSpherePdf() -> double { return PI_TIMES_4; }

auto Sampler::CosineSampleHemisphere() const -> math::Vector3d {
  auto const kD = ConcentricSampleDisk();
  auto const kZ = std::sqrt(std::max(0.0, 1 - kD.x * kD.x - kD.y * kD.y));
  return {kD.x, kD.y, kZ};
}

auto Sampler::CosineHemispherePdf(const double& cos) -> double {
  return cos * PI_INV;
}

auto Sampler::UniformSampleCone(const double& cosThetaMax) const
    -> math::Vector3d {
  auto const kU = UniformSample2D();
  auto const kCosTheta = 1 - kU.x + kU.x * cosThetaMax;
  auto const kSinTheta = std::sqrt(1 - kCosTheta * kCosTheta);
  auto const kPhi = kU.y * PI_TIMES_2;
  return {std::cos(kPhi) * kSinTheta, std::sin(kPhi) * kSinTheta, kCosTheta};
}

auto Sampler::UniformConePdf(const double& cosThetaMax) -> double {
  return 1 / (PI_TIMES_2 * (1 - cosThetaMax));
}

auto Sampler::UniformSampleDisk() const -> Vector2d {
  auto const kRad = UniformSample1D() * PI_TIMES_2;
  auto r = UniformSample1D();
  return {r * std::cos(kRad), r * std::sin(kRad)};
}

auto Sampler::ConcentricSampleDisk() const -> Vector2d {
  auto const kP = UniformSample2D() * 2 - Vector2d(1.0, 1.0);

  if (kP.x < EPSILON && kP.y < EPSILON) return {0, 0};
  double theta = NAN;
  double r = NAN;
  if (std::abs(kP.x) > std::abs(kP.y)) {
    r = kP.x;
    theta = PI_OVER_4 * (kP.y / kP.x);
  } else {
    r = kP.y;
    theta = PI_OVER_2 - PI_OVER_4 * (kP.x / kP.y);
  }
  return Vector2d(std::cos(theta), std::sin(theta)) * r;
}

auto Sampler::UniformSampleUInt1D(size_t const& to) const -> size_t {
  std::uniform_int_distribution<size_t> dist(0, to);
  return dist(rng_);
}

auto Sampler::UniformSampleUInt1D(size_t const& from, size_t const& to) const
    -> size_t {
  std::uniform_int_distribution dist(from, to);
  return dist(rng_);
}
}  // namespace cherry
