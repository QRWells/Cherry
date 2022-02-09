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

#pragma region PerspectiveCamera
PerspectiveCamera::PerspectiveCamera(const math::Point3& look_from,
                                     const math::Point3& look_at,
                                     const math::Vector3d& view_up,
                                     const double& fov,
                                     const double& aspect_ratio,
                                     const double& aperture,
                                     const double& focal_distance)
    : Camera(look_from, fov, aspect_ratio, aperture, focal_distance) {
  auto const kTheta = DegToRad(fov);
  auto const kH = tan(kTheta / 2);
  auto const kViewportHeight = 2.0 * kH;
  auto const kViewportWidth = kViewportHeight * aspect_ratio;

  w = (look_from - look_at).Normalized();
  u = view_up.Cross(w).Normalized();
  v = w.Cross(u);

  horizontal = kViewportWidth * u * focal_distance;
  vertical = -kViewportHeight * v * focal_distance;
  top_left = position - horizontal / 2 - vertical / 2 - w * focal_distance;
}

auto PerspectiveCamera::GenerateRay(const double& x, const double& y) const
    -> Ray {
  static const auto kLensRadius = aperture * 0.5;
  auto const kDist = GetRandomDoubleWithinCircle() * kLensRadius;
  auto const kOffset = kDist.x * u + kDist.y * v;
  return {position + kOffset,
          top_left + x * horizontal + y * vertical - position - kOffset};
}
#pragma endregion

#pragma region OrthographicCamera
OrthographicCamera::OrthographicCamera(const math::Point3& look_from,
                                       const math::Point3& look_at,
                                       const math::Vector3d& view_up,
                                       const double& fov,
                                       const double& aspect_ratio,
                                       const double& aperture,
                                       const double& focal_distance)
    : Camera(look_from, fov, aspect_ratio, aperture, focal_distance) {
  auto const kTheta = DegToRad(fov);
  auto const kH = tan(kTheta / 2);
  auto const kViewportHeight = 2.0 * kH;
  auto const kViewportWidth = kViewportHeight * aspect_ratio;

  w = (look_from - look_at).Normalized();
  u = view_up.Cross(w).Normalized();
  v = w.Cross(u);

  horizontal = kViewportWidth * u * focal_distance;
  vertical = -kViewportHeight * v * focal_distance;
  top_left = position - horizontal / 2 - vertical / 2 - w * focal_distance;
}

auto OrthographicCamera::GenerateRay(const double& x, const double& y) const
    -> Ray {
  static const auto kLensRadius = aperture * 0.5;
  auto const kDist = GetRandomDoubleWithinCircle() * kLensRadius;
  auto const kOffset = kDist.x * u + kDist.y * v;
  return {top_left + x * horizontal + y * vertical + kOffset, w};
}
#pragma endregion
}  // namespace cherry