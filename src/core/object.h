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
  virtual bool Intersect(const Ray &, Intersection &) const = 0;
  virtual Box GetBounds() = 0;
  virtual void Sample(Intersection &, double &) = 0;
  virtual void ComputeBox(std::vector<double> &, std::vector<double> &,
                          const math::Vector3d *) const {
    std::cerr << "virtual function called in Object :(\n";
    exit(-1);
  }

  [[nodiscard]] virtual bool HasEmission() const = 0;
  [[nodiscard]] virtual double GetSurfaceArea() const = 0;
};
}  // namespace cherry
#endif  // !OBJECT
