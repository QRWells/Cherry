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

#include <utility>
#include <vector>

#include "core/integrator.h"
#include "core/renderer.h"
#include "core/scene.h"

namespace cherry {

class RayTracer final : public Renderer {
 public:
  /**
   * \brief samples per pixel
   */
  size_t spp = 64;

  explicit RayTracer(const std::shared_ptr<Scene>& scene, const uint32_t& width,
                     const uint32_t& height,
                     std::shared_ptr<Integrator> integrator,
                     const size_t& spp = 64)
      : Renderer(scene, width, height),
        spp(spp),
        integrator_(std::move(integrator)) {
    scene->BuildBvh();
  }

  void Render() override;

 private:
  std::shared_ptr<Integrator> integrator_;
};
}  // namespace cherry

#endif  // !CHERRY_CORE_RAY_TRACER
