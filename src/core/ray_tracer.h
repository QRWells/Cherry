// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : ray_tracer.h
// Author      : QRWells
// Created at  : 2021/08/23 18:44
// Description :

#ifndef CHERRY_CORE_RAY_TRACER
#define CHERRY_CORE_RAY_TRACER

#include <string>
#include <vector>

#include "integrator.h"
#include "scene.h"

namespace cherry {

class RayTracer {
 public:
  /**
   * \brief samples per pixel
   */
  size_t spp_ = 64;

  explicit RayTracer(const std::shared_ptr<Scene>& scene, const uint32_t& width,
                     const uint32_t& height,
                     const std::shared_ptr<Integrator>& integrator,
                     const size_t& spp = 64)
      : spp_(spp),
        width_(width),
        height_(height),
        scene_(scene),
        frame_buffer_(width_ * height_),
        integrator_(integrator) {
    scene_->BuildBvh();
  }

  ~RayTracer() = default;

  void Render();
  void SavePpm(const std::string& file_name = "binary");

 private:
  uint32_t width_;
  uint32_t height_;
  std::shared_ptr<Scene> scene_;
  std::vector<math::Vector3d> frame_buffer_;
  std::shared_ptr<Integrator> integrator_;
};
}  // namespace cherry

#endif  // !CHERRY_CORE_RAY_TRACER
