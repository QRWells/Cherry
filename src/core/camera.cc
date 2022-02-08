// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : camera.cc
// Author      : QRWells
// Created at  : 2021/08/24 5:07
// Description :

#include "core/camera.h"

#include "math/vector.h"
#include "utility/random.h"

namespace cherry {
auto PerspectiveCamera::GenerateRay(const double& x, const double& y) const
    -> Ray {
  static const auto kLensRadius = aperture * 0.5;
  auto const kDist = GetRandomDoubleWithinCircle() * kLensRadius;
  auto const kOffset = kDist.x * u + kDist.y * v;
  return {position + kOffset,
          top_left + x * horizontal + y * vertical - position - kOffset};
}
}  // namespace cherry