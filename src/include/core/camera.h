// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : camera.h
// Author      : QRWells
// Created at  : 2021/08/24 5:07
// Description :

#ifndef CHERRY_CORE_CAMERA
#define CHERRY_CORE_CAMERA

#include "common/ray.h"
#include "utility/algorithm.h"

namespace cherry {
class Camera {
 public:
  Camera(const math::Point3& pos, const double& fov, const double& aspect_ratio,
         const double& aperture, const double& focal_distance)
      : aperture(aperture),
        focal_distance(focal_distance),
        fov(fov),
        aspect_ratio(aspect_ratio),
        position(pos) {}
  virtual ~Camera() = default;
  [[nodiscard]] virtual auto GenerateRay(const double& x, const double& y) const
      -> Ray = 0;

 protected:
  double aperture;
  double focal_distance;
  double fov;
  double aspect_ratio;
  math::Vector3d u, v, w;
  math::Vector3d position;
  math::Vector3d horizontal;
  math::Vector3d vertical;
  math::Point3 top_left;
};

class PerspectiveCamera final : public Camera {
 public:
  PerspectiveCamera(const math::Point3& look_from, const math::Point3& look_at,
                    const math::Vector3d& view_up, const double& fov,
                    const double& aspect_ratio, const double& aperture,
                    const double& focal_distance);
  [[nodiscard]] auto GenerateRay(const double& x, const double& y) const
      -> Ray override;
};

class OrthographicCamera final : public Camera {
 public:
  OrthographicCamera(const math::Point3& look_from, const math::Point3& look_at,
                     const math::Vector3d& view_up, const double& fov,
                     const double& aspect_ratio, const double& aperture,
                     const double& focal_distance);
  [[nodiscard]] auto GenerateRay(const double& x, const double& y) const
      -> Ray override;
};
}  // namespace cherry

#endif  // !CAMERA_H