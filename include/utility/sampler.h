/**
 * @file sampler.h
 * @author QRWells (qirui.wang@moegi.waseda.jp)
 * @brief Sampler used in rendering
 * @version 0.1
 * @date 2022-02-08
 *
 * @copyright Copyright (c) 2021 QRWells. All rights reserved.
 * Licensed under the MIT license.
 *
 */

#ifndef CHERRY_UTILITY_SAMPLER
#define CHERRY_UTILITY_SAMPLER

#include <initializer_list>
#include <random>

#include "math/vector.h"
#include "utility/constant.h"

namespace cherry {

/**
 * @brief 1-dimension distribution based on
 *
 */
struct Distribution1D {
  Distribution1D(std::initializer_list<double> list);

  /**
   * @brief
   *
   * @return double
   */
  [[nodiscard]] auto Count() const -> double;

  /**
   * @brief
   *
   * @param u
   * @param pdf
   * @param off
   * @return double
   */
  auto SampleContinuous(const double &u, double *pdf,
                        uint64_t *off = nullptr) const -> double;
  /**
   * @brief
   *
   * @param u
   * @param pdf
   * @param u_remapped
   * @return auto
   */
  auto SampleDiscrete(const double &u, double *pdf = nullptr,
                      double *u_remapped = nullptr) const;

  /**
   * @brief
   *
   * @param index
   * @return double
   */
  [[nodiscard]] auto DiscretePdf(const int &index) const -> double;

  std::vector<double> func, cdf;
  double func_int;
};

/**
 * @brief Simple sampler
 *
 */
class Sampler {
  Sampler() : rng_(dev_()) {}

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
