// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Cherry.
// File Name   : rasterizer.h
// Author      : QRWells
// Created at  : 2021/09/03 3:49
// Description :

#ifndef CHERRY_CORE_RASTERIZER
#define CHERRY_CORE_RASTERIZER

#include <memory>
#include <vector>

#include "../math/vector.h"
#include "renderer.h"
#include "scene.h"

namespace cherry {
class Rasterizer : public Renderer {
 public:
  explicit Rasterizer(const std::shared_ptr<Scene>& scene,
                      const uint32_t& width, const uint32_t& height)
      : Renderer(scene, width, height) {}

  void Render() override;
};
}  // namespace cherry

#endif  // !CHERRY_CORE_RASTERIZER
