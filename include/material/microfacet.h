// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : microfacet.h
// Author      : QRWells
// Created at  : 2021/09/02 3:10
// Description : The header file of microfacet material implemented
//               cook torrance method.

#ifndef CHERRY_MATERIAL_MICROFACET
#define CHERRY_MATERIAL_MICROFACET

#include "core/material.h"

namespace cherry {
class MicrofacetMaterial final : public Material {
 public:
  explicit MicrofacetMaterial(const math::Color &kd,
                              const double &roughness = 0.6,
                              const double &metallic = 1,
                              const math::Color &emit = {})
      : Material(kd, math::Vector3d(0.95), Attribute::kMicrofacet, emit),
        roughness_(roughness),
        metallic_(metallic) {}

  auto Evaluate(const math::Vector3d &wi, const math::Vector3d &wo,
                const math::Vector3d &n) -> math::Color override;
  auto Sample(const math::Vector3d &wi, const math::Vector3d &n)
      -> math::Color override;
  auto Pdf(const math::Vector3d &wi, const math::Vector3d &wo,
           const math::Vector3d &n) -> double override;

 private:
  double roughness_;
  double metallic_;
  inline const static math::Vector3d F0 = math::Vector3d(0.04);
};
}  // namespace cherry

#endif  // !CHERRY_MATERIAL_MICROFACET
