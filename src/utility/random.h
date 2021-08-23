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

#include "constant.h"
#include "../math/vector.h"

namespace cherry {
inline double GetRandomDouble() {
  static std::random_device dev;
  static std::mt19937 rng(dev());
  static std::uniform_real_distribution<double> dist(
      0, 1);  // distribution in range [0,1]

  return dist(rng);
}

inline math::Vector2d GetRandomDoubleWithinCircle() {
  auto const kRad = GetRandomDouble() * k2Pi;
  auto r = GetRandomDouble();
  return {r * std::cos(kRad), r * std::sin(kRad)};
}

inline size_t GetRandomUInt(size_t const& to) {
  static std::random_device dev;
  static std::mt19937 rng(dev());
  static std::uniform_int_distribution<size_t> dist(0, to);

  return dist(rng);
}

inline size_t GetRandomUInt(size_t const& from, size_t const& to) {
  static std::random_device dev;
  static std::mt19937 rng(dev());
  static std::uniform_int_distribution dist(from, to);

  return dist(rng);
}
}  // namespace cherry

#endif  // !CHERRY_UTILITY_RANDOM
