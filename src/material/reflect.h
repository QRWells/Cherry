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
  explicit ReflectMaterial(math::Color const &kd = {1.0, 1.0, 1.0},
                           math::Color const &ks = {0, 0, 0},
                           math::Color const &emit = {},
                           double const &ior = 1.4)
      : Material(kd, ks, Attribute::kReflect, emit, ior) {}
  auto Evaluate(const math::Vector3d &wi, const math::Vector3d &wo,
                const math::Vector3d &n) -> math::Color override;
  auto Sample(const math::Vector3d &wi, const math::Vector3d &n)
      -> math::Color override;
  auto Pdf(const math::Vector3d &wi, const math::Vector3d &wo,
           const math::Vector3d &n) -> double override;
};
}  // namespace cherry
#endif  // !CHERRY_MATERIAL_REFLECT