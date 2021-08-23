// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : reflect.h
// Author      : QRWells
// Created at  : 2021/09/04 5:18
// Description :

#ifndef CHERRY_MATERIAL_REFLECT
#define CHERRY_MATERIAL_REFLECT

#include "../core/material.h"

namespace cherry {
class ReflectMaterial final : public Material {
 public:
  explicit ReflectMaterial(math::Color const& kd = {1.0, 1.0, 1.0},
                           math::Color const& ks = {0, 0, 0},
                           math::Color const& emit = {},
                           double const& ior = 1.4)
      : Material(kd, ks, Attribute::kReflect, emit, ior) {}
  math::Color Evaluate(math::Vector3d const&, math::Vector3d const&,
                       math::Vector3d const&) override;
  math::Color Sample(math::Vector3d const&, math::Vector3d const&) override;
  double Pdf(math::Vector3d const&, math::Vector3d const&,
             math::Vector3d const&) override;
};
}  // namespace cherry
#endif  // !CHERRY_MATERIAL_REFLECT