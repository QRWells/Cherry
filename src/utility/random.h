// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : random.h
// Author      : QRWells
// Created at  : 2021/08/25 5:52
// Description :

#ifndef CHERRY_UTILITY_RANDOM
#define CHERRY_UTILITY_RANDOM

#include <random>

#include "../math/vector.h"
#include "constant.h"

namespace cherry {
inline auto GetRandomDouble() -> double {
  static std::random_device dev;
  static std::mt19937 rng(dev());
  static std::uniform_real_distribution<double> dist(
      0.0, 1.0);  // distribution in range [0,1]

  return dist(rng);
}

inline auto GetRandomDoubleWithinCircle() -> math::Vector2d {
  auto const kRad = GetRandomDouble() * PI_TIMES_2;
  auto r = GetRandomDouble();
  return {r * std::cos(kRad), r * std::sin(kRad)};
}

inline auto GetRandomUInt(size_t const& to) -> size_t {
  static std::random_device dev;
  static std::mt19937 rng(dev());
  std::uniform_int_distribution<size_t> dist(0U, to);

  return dist(rng);
}

inline auto GetRandomUInt(size_t const& from, size_t const& to) -> size_t {
  static std::random_device dev;
  static std::mt19937 rng(dev());
  std::uniform_int_distribution<size_t> dist(from, to);

  return dist(rng);
}
}  // namespace cherry

#endif  // !CHERRY_UTILITY_RANDOM
