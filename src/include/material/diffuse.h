// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : diffuse.h
// Author      : QRWells
// Created at  : 2021/08/26 2:41
// Description :

#ifndef CHERRY_MATERIAL_DIFFUSE
#define CHERRY_MATERIAL_DIFFUSE

#include "../core/material.h"

namespace cherry {
class DiffuseMaterial final : public Material {
 public:
  explicit DiffuseMaterial(const math::Color& kd, const math::Color& ks = {},
                           const math::Color& emit = {})
      : Material(kd, ks, Attribute::kDiffuse, emit) {}

  auto Evaluate(const math::Vector3d& wi, const math::Vector3d& wo,
                const math::Vector3d& n) -> math::Color override;
  auto Sample(const math::Vector3d& wi, const math::Vector3d& n)
      -> math::Color override;
  auto Pdf(const math::Vector3d& wi, const math::Vector3d& wo,
           const math::Vector3d& n) -> double override;
  // math::Color GetEmission() override;
};
}  // namespace cherry

#endif  // !CHERRY_MATERIAL_DIFFUSE
