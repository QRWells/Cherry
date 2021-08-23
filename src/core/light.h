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

#include "../common/intersection.h"
#include "../math/vector.h"
#include "object.h"

namespace cherry {
struct Light : Object {
  Light(double const& intensity) : intensity(intensity) {}
  double intensity = 0;

  bool Intersect(const Ray&, Intersection&) const override { return false; }
  Box GetBounds() override { return {}; }
  void Sample(Intersection&, double&) override = 0;
  [[nodiscard]] bool HasEmission() const override { return true; }
  [[nodiscard]] double GetSurfaceArea() const override { return 0; }
};
}  // namespace cherry

#endif  // !CHERRY_CORE_LIGHT
