// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : sampler.h
// Author      : QRWells
// Created at  : 2021/09/25 0:32
// Description :

#ifndef CHERRY_UTILITY_SAMPLER
#define CHERRY_UTILITY_SAMPLER

#include <random>

#include "../math/vector.h"
#include "constant.h"

namespace cherry {

template <typename T, typename Predicate>
auto FindInterval(const T &size, const Predicate &pred) -> T {
  T first = 0;
  T len = size;
  while (len > 0) {
    auto const kHalf = len >> 1;
    if (auto middle = first + kHalf; pred(middle)) {
      first = middle + 1;
      len -= kHalf + 1;
    } else
      len = kHalf;
  }
  return std::clamp(first - 1, 0UL, size - 2);
}

struct Distribution1D {
  Distribution1D(const double *f, const int &n) : func(f, f + n), cdf(n + 1) {
    cdf[0] = 0;
    for (int i = 1; i < n + 1; ++i) cdf[i] = cdf[i - 1] + func[i - 1] / n;

    func_int = cdf[n];
    if (func_int < EPSILON) {
      for (int i = 1; i < n + 1; ++i) cdf[i] = static_cast<double>(i) / n;
    } else {
      for (int i = 1; i < n + 1; ++i) cdf[i] /= func_int;
    }
  }

  [[nodiscard]] auto Count() const -> double {
    return static_cast<double>(func.size());
  }

  auto SampleContinuous(const double &u, double *pdf,
                        uint64_t *off = nullptr) const -> double {
    auto const kOffset = FindInterval(
        cdf.size(), [&](int const &index) { return cdf[index] <= u; });

    if (off != nullptr) *off = kOffset;
    double du = u - cdf[kOffset];
    if (cdf[kOffset + 1] - cdf[kOffset] > 0)
      du /= cdf[kOffset + 1] - cdf[kOffset];

    if (pdf != nullptr) *pdf = func[kOffset] / func_int;

    return (static_cast<double>(kOffset) + du) / Count();
  }

  auto SampleDiscrete(const double &u, double *pdf = nullptr,
                      double *u_remapped = nullptr) const {
    auto const kOffset = FindInterval(
        cdf.size(), [&](const int &index) { return cdf[index] <= u; });

    if (pdf != nullptr) *pdf = func[kOffset] / (func_int * Count());
    if (u_remapped != nullptr)
      *u_remapped = (u - cdf[kOffset]) / (cdf[kOffset + 1] - cdf[kOffset]);
    return kOffset;
  }

  [[nodiscard]] auto DiscretePdf(const int &index) const -> double {
    return func[index] / (func_int * Count());
  }

  std::vector<double> func, cdf;
  double func_int;
};

class Sampler {
  explicit Sampler() : rng_(dev_()) {}

  std::random_device dev_;
  std::mt19937 rng_;

 public:
  [[nodiscard]] auto UniformSample1D() const -> double;
  [[nodiscard]] auto UniformSample2D() const -> math::Vector2d;
  [[nodiscard]] auto UniformSampleDisk() const -> math::Vector2d;
  [[nodiscard]] auto ConcentricSampleDisk() const -> math::Vector2d;
  [[nodiscard]] auto UniformSampleUInt1D(size_t const &to) const -> size_t;
  [[nodiscard]] auto UniformSampleUInt1D(size_t const &from,
                                         size_t const &to) const -> size_t;
  [[nodiscard]] auto UniformSampleHemisphere() const -> math::Vector3d;
  [[nodiscard]] auto UniformSampleSphere() const -> math::Vector3d;
  [[nodiscard]] auto CosineSampleHemisphere() const -> math::Vector3d;
  [[nodiscard]] auto UniformSampleCone(const double &) const -> math::Vector3d;
  [[nodiscard]] static auto UniformHemispherePdf() -> double;
  [[nodiscard]] static auto UniformSpherePdf() -> double;
  [[nodiscard]] static auto CosineHemispherePdf(const double &) -> double;
  [[nodiscard]] static auto UniformConePdf(const double &) -> double;
};
}  // namespace cherry

#endif  // !CHERRY_UTILITY_SAMPLER
