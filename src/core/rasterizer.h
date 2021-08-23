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

#include <vector>
#include <memory>

#include "../math/vector.h"
#include "scene.h"

namespace cherry {
class Rasterizer {
 public:
  explicit Rasterizer(Scene* scene, const uint32_t& width,
                      const uint32_t& height)
      : width_(width), height_(height), scene_(scene) {}

  void Render();
  void SavePpm(const std::string& file_name = "binary");

 private:
  uint32_t width_;
  uint32_t height_;
  std::shared_ptr<Scene> scene_;
  std::vector<math::Color> frame_buffer_;
};
}  // namespace cherry

#endif  // !CHERRY_CORE_RASTERIZER
