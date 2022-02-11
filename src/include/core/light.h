// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : light.h
// Author      : QRWells
// Created at  : 2021/08/26 19:39
// Description :

#ifndef CHERRY_CORE_LIGHT
#define CHERRY_CORE_LIGHT

#include "common/intersection.h"
#include "math/vector.h"
#include "object.h"

namespace cherry {
struct Light : Object {
  explicit Light(double const& intensity) : intensity(intensity) {}
  double intensity = 0;

  auto Intersect(const Ray& ray, Intersection& inter) const -> bool override {
    return false;
  }
  auto GetBounds() -> Box override { return {}; }
  void Sample(Intersection& inter, double& d) override = 0;
  [[nodiscard]] auto HasEmission() const -> bool override { return true; }
  [[nodiscard]] auto GetSurfaceArea() const -> double override { return 0; }
};
}  // namespace cherry

#endif  // !CHERRY_CORE_LIGHT
