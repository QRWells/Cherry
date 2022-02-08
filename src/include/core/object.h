// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : object.h
// Author      : QRWells
// Created at  : 2021/08/23 22:03
// Description :

#ifndef CHERRY_CORE_OBJECT
#define CHERRY_CORE_OBJECT

#include <iostream>
#include <vector>

#include "../common/box.h"
#include "../common/intersection.h"
#include "../common/ray.h"

namespace cherry {
class Object {
 public:
  Object() = default;
  virtual ~Object() = default;
  virtual auto Intersect(const Ray &, Intersection &) const -> bool = 0;
  virtual auto GetBounds() -> Box = 0;
  virtual void Sample(Intersection &, double &) = 0;

  [[nodiscard]] virtual auto HasEmission() const -> bool = 0;
  [[nodiscard]] virtual auto GetSurfaceArea() const -> double = 0;
};
}  // namespace cherry
#endif  // !OBJECT
