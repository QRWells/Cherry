// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : camera.cc
// Author      : QRWells
// Created at  : 2021/08/24 5:07
// Description :

#include "camera.h"

#include "../math/matrix.h"
#include "../math/vector.h"
#include "../utility/random.h"

namespace cherry {
Ray PerspectiveCamera::GenerateRay(const double& x, const double& y) const {
  static const auto kLensRadius = aperture_ * 0.5;
  auto const kDist = GetRandomDoubleWithinCircle() * kLensRadius;
  auto const kOffset = kDist.x * u_ + kDist.y * v_;
  return {position_ + kOffset,
          top_left_ + x * horizontal_ + y * vertical_ - position_ - kOffset};
}
}  // namespace cherry