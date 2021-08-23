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

#include "../common/ray.h"
#include "../utility/algorithm.h"

namespace cherry {
class Camera {
 public:
  Camera(const math::Point3& pos, const double& fov, const double& aspect_ratio,
         const double& aperture, const double& focal_distance)
      : aperture_(aperture),
        focal_distance_(focal_distance),
        fov_(fov),
        aspect_ratio_(aspect_ratio),
        position_(pos) {}
  virtual ~Camera() = default;
  [[nodiscard]] virtual Ray GenerateRay(const double&,const double&) const = 0;

 protected:
  double aperture_;
  double focal_distance_;
  double fov_;
  double aspect_ratio_;
  math::Vector3d u_, v_, w_;
  math::Vector3d position_;
  math::Vector3d horizontal_;
  math::Vector3d vertical_;
  math::Point3 top_left_;
};

class PerspectiveCamera final : public Camera {
 public:
  PerspectiveCamera(const math::Point3& look_from, const math::Point3& look_at,
                    const math::Vector3d view_up, const double& fov,
                    const double& aspect_ratio, const double& aperture,
                    const double& focal_distance)
      : Camera(look_from, fov, aspect_ratio, aperture, focal_distance) {
    auto const kTheta = DegToRad(fov_);
    auto const kH = tan(kTheta / 2);
    auto const kViewportHeight = 2.0 * kH;
    auto const kViewportWidth = kViewportHeight * aspect_ratio_;

    w_ = (look_from - look_at).Normalized();
    u_ = view_up.Cross(w_).Normalized();
    v_ = w_.Cross(u_);

    horizontal_ = kViewportWidth * u_ * focal_distance_;
    vertical_ = -kViewportHeight * v_ * focal_distance_;
    top_left_ =
        position_ - horizontal_ / 2 - vertical_ / 2 - w_ * focal_distance_;
  }
  [[nodiscard]] Ray GenerateRay(const double&, const double&) const override;
};

class OrthographicCamera final : public Camera {
 public:
  [[nodiscard]] Ray GenerateRay(const double&, const double&) const override;
};
}  // namespace cherry

#endif  // !CAMERA_H