// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
// 
// This file is part of Project Cherry.
// File Name   : dielectric.h
// Author      : QRWells
// Created at  : 2021/09/09 7:24
// Description :

#ifndef CHERRY_MATERIAL_DIELECTRIC
#define CHERRY_MATERIAL_DIELECTRIC

#include "../core/material.h"

namespace cherry {
class DielectricMaterial final : public Material {
 public:
  DielectricMaterial(math::Vector3d const& kd, math::Vector3d const& ks,
                     double const& ior = 1.4)
      : Material(kd, ks, Attribute::kDielectric, {}, ior) {}

  math::Color Evaluate(math::Vector3d const&, math::Vector3d const&,
                       math::Vector3d const&) override;
  math::Vector3d Sample(math::Vector3d const&, math::Vector3d const&) override;
  double Pdf(math::Vector3d const&, math::Vector3d const&,
             math::Vector3d const&) override;
};
}  // namespace cherry

#endif  // !CHERRY_MATERIAL_DIELECTRIC