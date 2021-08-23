// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : reflect.cc
// Author      : QRWells
// Created at  : 2021/09/04 5:18
// Description :

#include "reflect.h"

#include "../utility/algorithm.h"
#include "../utility/constant.h"

using namespace cherry::math;

namespace cherry {
Color ReflectMaterial::Evaluate(Vector3d const& wi, Vector3d const& wo,
                                Vector3d const& n) {
  auto const kD = 1 - Fresnel(wi.Normalized(), n, 1, ior_);
  auto const kS = CookTorrance(wi, wo, n, 2, 1, ior_);
  return n.Dot(wo) > 0.0 ? ks_ * kS + kD * kd_ * kPiInv : Color(0.0);
}

Color ReflectMaterial::Sample(Vector3d const& wi, Vector3d const& n) {
  return Reflect(wi.Normalized(), n);
}
double ReflectMaterial::Pdf(Vector3d const& wi, Vector3d const& wo,
                            Vector3d const& n) {
  return 1;
}
}  // namespace cherry
