/**
 * @file sampler.cc
 * @author QRWells (qirui.wang@moegi.waseda.jp)
 * @brief Implementations of classes in sampler.h
 * @version 0.1
 * @date 2022-02-08
 *
 * @copyright Copyright (c) 2021 QRWells. All rights reserved.
 * Licensed under the MIT license.
 *
 */

#include "utility/sampler.h"

#include <cstddef>

#include "utility/constant.h"

namespace cherry {
using namespace math;

#pragma region HelperMethods

/**
 * @brief
 *
 * @tparam T
 * @tparam Predicate
 * @param size
 * @param pred
 * @return T
 */
template <typename T, typename Predicate>
auto FindInterval(const T& size, const Predicate& pred) -> T {
  T first = 0;
  T len = size;
  while (len > 0) {
    auto half = len >> 1;
    if (auto middle = first + half; pred(middle)) {
      first = middle + 1;
      len -= half + 1;
    } else {
      len = half;
    }
  }
  return std::clamp(first - 1, 0UL, size - 2);
}

#pragma endregion

#pragma region Distribution1D

Distribution1D::Distribution1D(std::initializer_list<double> list)
    : func(list), cdf(list.size() + 1) {
  cdf[0] = 0;
  auto&& n = list.size();
  for (int i = 1; i < n + 1; ++i)
    cdf[i] = cdf[i - 1] + func[i - 1] / static_cast<double>(n);

  func_int = cdf[n];
  if (func_int < EPSILON)
    for (int i = 1; i < n + 1; ++i)
      cdf[i] = static_cast<double>(i) / static_cast<double>(n);
  else
    for (int i = 1; i < n + 1; ++i) cdf[i] /= func_int;
}

auto Distribution1D::DiscretePdf(const int& index) const -> double {
  return func[index] / (func_int * Count());
}

auto Distribution1D::SampleDiscrete(const double& u, double* pdf,
                                    double* u_remapped) const {
  auto const kOffset = FindInterval(
      cdf.size(), [&](size_t const& index) { return cdf[index] <= u; });

  if (pdf != nullptr) *pdf = func[kOffset] / (func_int * Count());
  if (u_remapped != nullptr)
    *u_remapped = (u - cdf[kOffset]) / (cdf[kOffset + 1] - cdf[kOffset]);
  return kOffset;
}

auto Distribution1D::SampleContinuous(const double& u, double* pdf,
                                      uint64_t* off) const -> double {
  auto const kOffset = FindInterval(
      cdf.size(), [&](size_t const& index) { return cdf[index] <= u; });

  if (off != nullptr) *off = kOffset;
  double du = u - cdf[kOffset];
  if (cdf[kOffset + 1] - cdf[kOffset] > 0)
    du /= cdf[kOffset + 1] - cdf[kOffset];

  if (pdf != nullptr) *pdf = func[kOffset] / func_int;

  return (static_cast<double>(kOffset) + du) / Count();
}
auto Distribution1D::Count() const -> double {
  return static_cast<double>(func.size());
}
#pragma endregion

#pragma region Sampler

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
#pragma endregion
}  // namespace cherry
